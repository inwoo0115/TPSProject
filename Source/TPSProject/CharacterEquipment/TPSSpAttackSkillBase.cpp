// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "Character/TPSCharacterBase.h"	
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPSSpAttackSkillData.h"

void ATPSSpAttackSkillBase::BeginPlay()
{
    Super::BeginPlay();

    if (EventSystem)
    {
        // UI Update
        EventSystem->OnSpAttackCoolTimeChange.Broadcast(SkillContext.CoolTime, SkillContext.CoolTime);
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

        // ����ź ����ü�� ��������� ������ ����
        if (Projectile)
        {
            //Event System ��� ������ ����
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
    }
}

void ATPSSpAttackSkillBase::InitializeAbilities()
{
    // ���ؽ�Ʈ ��� Ư�� ����
}

FSpAttackSkillContext ATPSSpAttackSkillBase::GetSkillContext() const
{
    return SkillContext;
}

void ATPSSpAttackSkillBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATPSSpAttackSkillBase, SkillContext);
    DOREPLIFETIME(ATPSSpAttackSkillBase, bCanCast);
    DOREPLIFETIME(ATPSSpAttackSkillBase, SkillData);
}
