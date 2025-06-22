// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPSDroneSkillData.h"
#include "Character/TPSCharacterBase.h"
#include "Summons/TPSSkillRangeDecalBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

void ATPSDroneSkillBase::BeginPlay()
{
    Super::BeginPlay();

    if (EventSystem)
    {
        // UI Update
        EventSystem->OnDroneCoolTimeChange.Broadcast(SkillContext.CoolTime, SkillContext.CoolTime);
    }

    // 스탯 변경 델리게이트 바인딩
    auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (GameplayEventInterface)
    {
        OnFieldChangedHandle = GameplayEventInterface->GetEventComponent()->OnDroneFieldChangeEvent.AddUObject(this, &ATPSDroneSkillBase::ChangeFieldStatByValue);
    }
}

void ATPSDroneSkillBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

    // 스탯 변경 델리게이트 제거
    auto GameplayEventInterface = Cast<ITPSEventComponentInterface>(GetOwner());
    if (GameplayEventInterface)
    {
        GameplayEventInterface->GetEventComponent()->OnDroneFieldChangeEvent.Remove(OnFieldChangedHandle);
    }
}

void ATPSDroneSkillBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 쿨타임 진행 중 일때 UI 업데이트
    if (!bCanCast)
    {
        auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());
        if (EventSystem && Character->IsLocallyControlled())
        {
            CurrentCoolTime += DeltaTime;
            if (CurrentCoolTime >= SkillContext.CoolTime)
            {
                bCanCast = true;
            }
            // UI Update
            EventSystem->OnDroneCoolTimeChange.Broadcast(CurrentCoolTime, SkillContext.CoolTime);
        }
    }
}

void ATPSDroneSkillBase::ShowUI()
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

void ATPSDroneSkillBase::CastSkill()
{
    // 스킬 실행
    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    if (Character)
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

        float Distance = FVector::Dist(TargetPoint, TraceStart);
        if (Distance < 3000.0f)
        {
            // 드론 스폰
            FActorSpawnParameters SpawnParams;

            SpawnParams.Owner = GetOwner();

            SpawnParams.Instigator = GetInstigator();

            auto Drone = GetWorld()->SpawnActor<ATPSDroneActorBase>(
                DroneActorList[SkillContext.CurrentDroneActor],
                TargetPoint,
                FRotator(0, 0, 0),
                SpawnParams
            );

            if (Drone)
            {
                // 드론 내부 변수 설정
                Drone->Power = SkillContext.Power;
                Drone->LifeTime = SkillContext.LifeTime;
                Drone->OverlapRatio = SkillContext.Duration;
                Drone->UltiGaugeRatio = SkillContext.UltiGaugeRatio;
            }
        }
    }
}

void ATPSDroneSkillBase::LaunchSkill()
{
    // 범위 밖일 경우 무효
    if (!TargetRange)
    {
		return;
    }

    bCanCast = false;

    // Cast Cool Time Start
    CurrentCoolTime = 0.0f;

    auto Character = Cast<ATPSCharacterBase>(OwnerComponent->GetOwner());

    if (TargetRange && Character->IsLocallyControlled())
    {
        TargetRange->Destroy();
        TargetRange = nullptr;
    }


    // Cast Delay
    /*GetWorld()->GetTimerManager().SetTimer(CastCooldownHandle, FTimerDelegate::CreateLambda([this]()
        {
            bCanCast = true;
        }), SkillContext.CoolTime, false);*/
}

bool ATPSDroneSkillBase::GetCanCast()
{
    return bCanCast;
}

void ATPSDroneSkillBase::SetSkillContextFromData()
{
    if (SkillData)
    {
        AbilityList = SkillData->AbilityList;

        DroneActorList = SkillData->DroneActorList;

        SkillContext.Power = SkillData->Power;

        SkillContext.CoolTime = SkillData->CoolTime;

        SkillContext.UltiGaugeRatio = SkillData->UltiGaugeRatio;

        SkillContext.SkillEquipmentIcon = SkillData->SkillEquipmentIcon;

        SkillContext.SkillEquipmentName = SkillData->SkillEquipmentName;

        SkillContext.CurrentDroneActor = SkillData->CurrentDroneActor;

        SkillContext.RangeDecal = SkillData->RangeDecal;

        SkillContext.LifeTime = SkillData->LifeTime;
    }
}

void ATPSDroneSkillBase::InitializeAbilities()
{
    // 컨텍스트 기반 특성 적용
    for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
    {
        if (Ability)
        {
            Ability->InitializeDroneAbility(SkillContext);
        }
    }
}

FDroneSkillContext ATPSDroneSkillBase::GetSkillContext() const
{
	return SkillContext;
}

void ATPSDroneSkillBase::ChangeFieldStatByValue(FName FieldName, float Value)
{
    // 1) 클래스 내부에서 FieldName을 가진 FProperty 찾기
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
    // 2) FDroneSkillContext 내부에서 FieldName을 가진 FProperty 찾기
    UScriptStruct* ContextStruct = FDroneSkillContext::StaticStruct();
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

void ATPSDroneSkillBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATPSDroneSkillBase, SkillContext);
    DOREPLIFETIME(ATPSDroneSkillBase, bCanCast);
    DOREPLIFETIME(ATPSDroneSkillBase, SkillData);
}
