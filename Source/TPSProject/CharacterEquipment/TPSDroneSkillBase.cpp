// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "TPSDroneSkillData.h"


void ATPSDroneSkillBase::BeginPlay()
{
    Super::BeginPlay();

    if (EventSystem)
    {
        // UI Update
        EventSystem->OnDroneCoolTimeChange.Broadcast(SkillContext.CoolTime, SkillContext.CoolTime);
    }
}

void ATPSDroneSkillBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ��Ÿ�� ���� �� �϶� UI ������Ʈ
    if (!bCanCast)
    {
        if (EventSystem)
        {
            CurrentCoolTime += DeltaTime;

            // UI Update
            EventSystem->OnDroneCoolTimeChange.Broadcast(CurrentCoolTime, SkillContext.CoolTime);
        }
    }
}

void ATPSDroneSkillBase::ShowUI()
{
    // ��ġ ��ġ UI
}

void ATPSDroneSkillBase::Cast()
{
    // ��ų ����
}

void ATPSDroneSkillBase::Launch()
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

bool ATPSDroneSkillBase::GetCanCast()
{
    return bCanCast;
}

void ATPSDroneSkillBase::SetSkillContextFromData()
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

void ATPSDroneSkillBase::InitializeAbilities()
{
    // ���ؽ�Ʈ ��� Ư�� ����
}

FDroneSkillContext ATPSDroneSkillBase::GetSkillContext() const
{
	return SkillContext;
}

void ATPSDroneSkillBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ATPSDroneSkillBase, SkillContext);
    DOREPLIFETIME(ATPSDroneSkillBase, bCanCast);
    DOREPLIFETIME(ATPSDroneSkillBase, SkillData);
}
