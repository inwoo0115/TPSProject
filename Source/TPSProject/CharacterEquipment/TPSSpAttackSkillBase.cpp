// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSSpAttackSkillBase.h"
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

    // 쿨타임 진행 중 일때 UI 업데이트
    if (!bCanCast)
    {
        if (EventSystem)
        {
            CurrentCoolTime += DeltaTime;

            // UI Update
            EventSystem->OnSpAttackCoolTimeChange.Broadcast(CurrentCoolTime, SkillContext.CoolTime);
        }
    }
}

void ATPSSpAttackSkillBase::Cast()
{
    // 스킬 실행
}

void ATPSSpAttackSkillBase::Launch()
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
        AbilityList = SkillData->AbilityList;

        SkillContext.Damage = SkillData->Damage;

        SkillContext.CoolTime = SkillData->CoolTime;

        SkillContext.UltiGaugeRatio = SkillData->UltiGaugeRatio;

        SkillContext.SkillEquipmentIcon = SkillData->SkillEquipmentIcon;

        SkillContext.SkillEquipmentName = SkillData->SkillEquipmentName;
    }
}

void ATPSSpAttackSkillBase::InitializeAbilities()
{
    // 컨텍스트 기반 특성 적용
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
