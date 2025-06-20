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

    // 게이지 업데이트 함수 바인딩
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
    // 설치 위치 UI
    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    if (Character && Character->IsLocallyControlled())
    {
        // 카메라 기준 라인트레이스
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
    CurrentGauge = 0.0f;

    // 스킬 실행
    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    if (Character)
    {
        // 궁극기 액터 스폰
        FActorSpawnParameters SpawnParams;

        SpawnParams.Owner = GetOwner();

        SpawnParams.Instigator = GetInstigator();

        auto Ulti = GetWorld()->SpawnActor<ATPSUltimateActorBase>(
            UltimateActorList[SkillContext.CurrentUltimate],
            TargetLocation,
            FRotator(0, 0, 0),
            SpawnParams
        );

        if (Ulti)
        {
            Ulti->Damage = SkillContext.Damage;
            Ulti->LifeTime = SkillContext.LifeTime;
        }
    }
}

void ATPSUltimateSkillBase::LaunchSkill()
{
    // 범위 밖일 경우 무효
    if (!TargetRange)
    {
        return;
    }

    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    // 서버 rpc 호출
    TargetLocation = TargetRange->GetActorLocation();

    if (TargetRange && Character->IsLocallyControlled())
    {
        TargetRange->Destroy();
        TargetRange = nullptr;
    }
}

bool ATPSUltimateSkillBase::GetCanCast()
{
    return CurrentGauge == SkillContext.MaxGauge;
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
    }
}

void ATPSUltimateSkillBase::InitializeAbilities()
{
    // 특성 적용
}

FUltimateSkillContext ATPSUltimateSkillBase::GetSkillContext() const
{
	return SkillContext;
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
