// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "Character/TPSCharacterBase.h"	
#include "Interface/TPSEventComponentInterface.h"  
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Net/UnrealNetwork.h"
#include "TPSUltimateSkillData.h"

void ATPSUltimateSkillBase::BeginPlay()
{
    Super::BeginPlay();

    // ������ ������Ʈ �Լ� ���ε�
    auto EventComponent = Cast<ITPSEventComponentInterface>(GetOwner());
    if (EventComponent)
    {
       DelegateHandle = EventComponent->GetEventComponent()->OnUltiGaugeUpdateEvent.AddUObject(this, &ATPSUltimateSkillBase::UpdateGauge);
    }

    auto Character = Cast<ATPSCharacterBase>(GetOwner());
    if (Character && Character->IsLocallyControlled())
    {
        EventSystem->OnUltimateGaugeChange.Broadcast(CurrentGauge, SkillContext.MaxGauge);
    }

    // ���� ���� ��������Ʈ ���ε�
    auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (GameplayEventInterface)
    {
        OnFieldChangedHandle = GameplayEventInterface->GetEventComponent()->OnUltimateFieldChangeEvent.AddUObject(this, &ATPSUltimateSkillBase::ChangeFieldStatByValue);
    }
}

void ATPSUltimateSkillBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    ClearUpdateDelegate();
    // ���� ���� ��������Ʈ ����
    auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (GameplayEventInterface)
    {
        GameplayEventInterface->GetEventComponent()->OnUltimateFieldChangeEvent.Remove(OnFieldChangedHandle);
    }
}

void ATPSUltimateSkillBase::UpdateGauge(float AddGauge)
{
    if (CurrentGauge + AddGauge > SkillContext.MaxGauge)
    {
        CurrentGauge = SkillContext.MaxGauge;
    }
    else
    {
        CurrentGauge += AddGauge;
    }

    auto Character = Cast<ATPSCharacterBase>(GetOwner());
    if (Character && Character->IsLocallyControlled())
    {
        EventSystem->OnUltimateGaugeChange.Broadcast(CurrentGauge, SkillContext.MaxGauge);
    }
}

void ATPSUltimateSkillBase::ShowUI()
{
    // ��ġ ��ġ UI
    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    if (Character && Character->IsLocallyControlled())
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

        // Spawn Params
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = GetOwner();
        SpawnParams.Instigator = GetInstigator();

        float Distance = FVector::Dist(TargetPoint, TraceStart);
        if (Distance < 3000.0f)
        {
            if (TargetRange)
            {
                TargetRange->SetActorLocation(TargetPoint);
            }
            else
            {
                TargetRange = GetWorld()->SpawnActor<ATPSSkillRangeDecalBase>(
                    SkillContext.RangeDecal,
                    TargetPoint,
                    FRotator(0, 0, 0),
                    SpawnParams
                );
            }
        }
        else
        {
            if (TargetRange)
            {
                TargetRange->Destroy();
                TargetRange = nullptr;
            }
        }
    }
}

void ATPSUltimateSkillBase::CastSkill()
{
    // ��ų ����
    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    CurrentGauge = 0.0f;

    if (Character)
    {
        const int32 NumEffects = SkillContext.AttackTimes;
        const float Radius = SkillContext.AttackRadius;      // ��ȯ �ݰ�
        const FVector OriginLocation = TargetLocation;       // �߽� ��ġ

        for (int32 i = 0; i < NumEffects; i++)
        {
            float RandomDelay = FMath::FRandRange(0.f, 1.5f); // 0~1�� ����
            FTimerHandle TimerHandle;

            // ���� ĸ��
            GetWorld()->GetTimerManager().SetTimer(
                TimerHandle,
                [this, OriginLocation, Radius]()
                {
                    FVector RandomOffset(FMath::FRandRange(-Radius, Radius),
                        FMath::FRandRange(-Radius, Radius),
                        0.f);

                    FVector SpawnLocation = OriginLocation + RandomOffset;

                    FActorSpawnParameters SpawnParams;
                    SpawnParams.Owner = GetOwner();
                    SpawnParams.Instigator = GetInstigator();

                    auto Ulti = GetWorld()->SpawnActor<ATPSUltimateActorBase>(
                        UltimateActorList[SkillContext.CurrentUltimate],
                        SpawnLocation,
                        FRotator::ZeroRotator,
                        SpawnParams
                    );

                    if (Ulti)
                    {
                        Ulti->Damage = SkillContext.Damage;
                        Ulti->LifeTime = SkillContext.LifeTime;
                    }
                },
                RandomDelay, false
            );
        }
    }
}

void ATPSUltimateSkillBase::LaunchSkill()
{
    // ���� ���� ��� ��ȿ
    if (!TargetRange)
    {
        bIsInRange = false;
        return;
    }

    auto EventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (EventInterface)
    {
        EventInterface->GetEventComponent()->OnUltimateCastEvent.Broadcast(TargetRange->GetActorLocation());
    }


    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    // ���� rpc ȣ��
    ServerRPCTargetLocation(TargetRange->GetActorLocation());

    // �ñر� ������ UI ����
    CurrentGauge = 0.0f;
    if (Character && Character->IsLocallyControlled())
    {
        EventSystem->OnUltimateGaugeChange.Broadcast(CurrentGauge, SkillContext.MaxGauge);

        // Target UI ����
        if (TargetRange)
        {
            TargetRange->Destroy();
            TargetRange = nullptr;
        }
    }

    bIsInRange = true;
}

bool ATPSUltimateSkillBase::GetCanCast()
{
    return CurrentGauge == SkillContext.MaxGauge;
}

bool ATPSUltimateSkillBase::GetInRange()
{
    return bIsInRange;
}

void ATPSUltimateSkillBase::ClearUpdateDelegate()
{
    auto EventComponent = Cast<ITPSEventComponentInterface>(GetOwner());
    if (EventComponent)
    {
        EventComponent->GetEventComponent()->OnUltiGaugeUpdateEvent.Remove(DelegateHandle);
    }
}

void ATPSUltimateSkillBase::SetSkillContextFromData()
{
    if (SkillData)
    {
        AbilityList = SkillData->AbilityList;

        SkillContext.Damage = SkillData->Damage;

        CurrentGauge = 0.0f;

        SkillContext.MaxGauge = SkillData->UltiGauge;

        SkillContext.SkillEquipmentIcon = SkillData->SkillEquipmentIcon;

        SkillContext.SkillEquipmentName = SkillData->SkillEquipmentName;

        SkillContext.RangeDecal = SkillData->RangeDecal;

        UltimateActorList = SkillData->UltimateActorList;

        SkillContext.CurrentUltimate = SkillData->CurrentUltimate;

        SkillContext.LifeTime = SkillData->LifeTime;

        SkillContext.AttackTimes = SkillData->AttackTimes;

        SkillContext.AttackRadius = SkillData->AttackRadius;
    }
}

void ATPSUltimateSkillBase::DeleteTargetUI()
{
    if (TargetRange)
    {
        TargetRange->Destroy();
        TargetRange = nullptr;
    }
}

void ATPSUltimateSkillBase::InitializeAbilities()
{
    // Ư�� ����
    for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
    {
        if (Ability)
        {
            Ability->InitializeUltimateAbility(SkillContext);
        }
    }
}

FUltimateSkillContext ATPSUltimateSkillBase::GetSkillContext() const
{
	return SkillContext;
}

void ATPSUltimateSkillBase::ChangeFieldStatByValue(FName FieldName, float Value)
{
    // 1) Ŭ���� ���ο��� FieldName�� ���� FProperty ã��
    FProperty* FoundProperty = GetClass()->FindPropertyByName(FieldName);
    if (FoundProperty)
    {
        if (FFloatProperty* FloatProp = CastField<FFloatProperty>(FoundProperty))
        {
            float NewValue = FloatProp->GetPropertyValue_InContainer(this) + Value;

            UE_LOG(LogTemp, Warning, TEXT("%f"), NewValue);

            FloatProp->SetPropertyValue_InContainer(this, NewValue);
            return;
        }
    }
    // 2) FDroneSkillContext ���ο��� FieldName�� ���� FProperty ã��
    UScriptStruct* ContextStruct = FUltimateSkillContext::StaticStruct();
    FProperty* ContextProp = ContextStruct->FindPropertyByName(FieldName);
    if (ContextProp)
    {
        if (FFloatProperty* FloatProp = CastField<FFloatProperty>(ContextProp))
        {
            float NewValue = FloatProp->GetPropertyValue_InContainer(this) + Value;
            FloatProp->SetPropertyValue_InContainer(&SkillContext, NewValue);
            return;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No matching field named %s found in class or SkillContext"), *FieldName.ToString());
    }
}

void ATPSUltimateSkillBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATPSUltimateSkillBase, SkillContext);
    DOREPLIFETIME(ATPSUltimateSkillBase, SkillData);
    DOREPLIFETIME(ATPSUltimateSkillBase, CurrentGauge);
}

void ATPSUltimateSkillBase::OnRepGaugeChanged()
{
    auto Character = Cast<ATPSCharacterBase>(GetOwner());
    if (Character && Character->IsLocallyControlled())
    {
        EventSystem->OnUltimateGaugeChange.Broadcast(CurrentGauge, SkillContext.MaxGauge);
    }
}

void ATPSUltimateSkillBase::ServerRPCTargetLocation_Implementation(FVector NewLocation)
{
    TargetLocation = NewLocation;
}
