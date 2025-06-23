// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "Character/TPSCharacterBase.h"	
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPSSpAttackSkillData.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

void ATPSSpAttackSkillBase::BeginPlay()
{
    Super::BeginPlay();

    if (EventSystem)
    {
        // UI Update
        EventSystem->OnSpAttackCoolTimeChange.Broadcast(SkillContext.CoolTime, SkillContext.CoolTime);
    }
    // ���� ���� ��������Ʈ ���ε�
    auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (GameplayEventInterface)
    {
        OnFieldChangedHandle = GameplayEventInterface->GetEventComponent()->OnSpAttackFieldChangeEvent.AddUObject(this, &ATPSSpAttackSkillBase::ChangeFieldStatByValue);
    }
}

void ATPSSpAttackSkillBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    // ���� ���� ��������Ʈ ����
    auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (GameplayEventInterface)
    {
        GameplayEventInterface->GetEventComponent()->OnSpAttackFieldChangeEvent.Remove(OnFieldChangedHandle);
    }
}

void ATPSSpAttackSkillBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ��Ÿ�� ���� �� �϶� UI ������Ʈ
    if (!bCanCast)
    {
        auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());
        if (EventSystem && Character->IsLocallyControlled())
        {
            CurrentCoolTime += DeltaTime;

            // UI Update
            EventSystem->OnSpAttackCoolTimeChange.Broadcast(CurrentCoolTime, SkillContext.CoolTime);
        }
    }
}

void ATPSSpAttackSkillBase::CastSkill()
{
    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());
    if (Character)
    {
        // ī�޶� ���� ����Ʈ���̽�
        FVector CameraLocation = Character->GetCameraLocation();
        FRotator CameraRotation = Character->GetCameraRotation();

        FVector TraceStart = CameraLocation + CameraRotation.Vector() * 100.0f;
        FVector TraceEnd = TraceStart + CameraRotation.Vector() * 10000.0f;

        FHitResult HitResult;
        FCollisionQueryParams TraceParams;
        TraceParams.AddIgnoredActor(this);
        TraceParams.AddIgnoredActor(GetOwner());

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
        FVector TargetPoint = bHit ? HitResult.ImpactPoint : TraceEnd;

        // �ѱ� ��ġ���� Ÿ�� ���� ���
        FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
        FVector ShotDirection = (TargetPoint - MuzzleLocation).GetSafeNormal();
        FRotator ShotRotation = ShotDirection.Rotation();

        // ����ü ����
        FActorSpawnParameters SpawnParams;

        SpawnParams.Owner = GetOwner();

        SpawnParams.Instigator = GetInstigator();

        // ����ü Ŭ������ ����
        auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
            ProjectileList[SkillContext.CurrentProjectile],
            MuzzleLocation,
            ShotRotation,
            SpawnParams
        );

        // ����ź ����ü�� ��������� ���� ����
        if (Projectile)
        {
            Projectile->Damage = SkillContext.Damage;
            Projectile->UltiGaugeRatio = SkillContext.UltiGaugeRatio;
			Projectile->ExplosionRadius = SkillContext.ExplosionRadius; 
        }
    }
}

void ATPSSpAttackSkillBase::LaunchSkill()
{
    bCanCast = false;

    // Cast Cool Time Start
    CurrentCoolTime = 0.0f;

    // Cast Delay
    GetWorld()->GetTimerManager().SetTimer(CastCooldownHandle, FTimerDelegate::CreateLambda([this]()
        {
            bCanCast = true;
        }), SkillContext.CoolTime, false);
    
}

bool ATPSSpAttackSkillBase::GetCanCast()
{
    return bCanCast;
}

void ATPSSpAttackSkillBase::SetSkillContextFromData()
{
    if (SkillData)
    {
        ProjectileList = SkillData->ProjectileList;

        AbilityList = SkillData->AbilityList;

        SkillContext.Damage = SkillData->Damage;

        SkillContext.CoolTime = SkillData->CoolTime;

        SkillContext.UltiGaugeRatio = SkillData->UltiGaugeRatio;

        SkillContext.SkillEquipmentIcon = SkillData->SkillEquipmentIcon;

        SkillContext.SkillEquipmentName = SkillData->SkillEquipmentName;

        SkillContext.CurrentProjectile = SkillData->CurrentProjectile;

		SkillContext.ExplosionRadius = SkillData->ExplosionRadius;
    }
}

void ATPSSpAttackSkillBase::InitializeAbilities()
{
    // ���ؽ�Ʈ ��� Ư�� ����
    for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
    {
        if (Ability)
        {
            Ability->InitializeSpAttackAbility(SkillContext);
        }
    }
}

FSpAttackSkillContext ATPSSpAttackSkillBase::GetSkillContext() const
{
    return SkillContext;
}

void ATPSSpAttackSkillBase::ChangeFieldStatByValue(FName FieldName, float Value)
{
    // 1) Ŭ���� ���ο��� FieldName�� ���� FProperty ã��
    FProperty* FoundProperty = GetClass()->FindPropertyByName(FieldName);
    if (FoundProperty)
    {
        if (FFloatProperty* FloatProp = CastField<FFloatProperty>(FoundProperty))
        {
            float NewValue = FloatProp->GetPropertyValue_InContainer(this) + Value;

            FloatProp->SetPropertyValue_InContainer(this, NewValue);
            return;
        }
    }
    // 2) FDroneSkillContext ���ο��� FieldName�� ���� FProperty ã��
    UScriptStruct* ContextStruct = FSpAttackSkillContext::StaticStruct();
    FProperty* ContextProp = ContextStruct->FindPropertyByName(FieldName);
    if (ContextProp)
    {
        if (FFloatProperty* FloatProp = CastField<FFloatProperty>(ContextProp))
        {
            // ���� Ŭ������ WeaponContext ��� �޸� ��������
            void* ContextAddr = FindFieldChecked<FStructProperty>(GetClass(), TEXT("SkillContext"))
                ->ContainerPtrToValuePtr<void>(this);

            // ���� ��
            float CurrentValue = FloatProp->GetPropertyValue_InContainer(ContextAddr);
            float NewValue = CurrentValue + Value;

            // ����
            FloatProp->SetPropertyValue_InContainer(ContextAddr, NewValue);
            return;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching field named %s found in class or SkillContext"), *FieldName.ToString());
    }
}

void ATPSSpAttackSkillBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATPSSpAttackSkillBase, SkillContext);
    DOREPLIFETIME(ATPSSpAttackSkillBase, bCanCast);
    DOREPLIFETIME(ATPSSpAttackSkillBase, SkillData);
}
