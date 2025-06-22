// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSBasicGrenade.h"
#include "CharacterEquipment/TPSSpAttackSkillData.h"

ATPSBasicGrenade::ATPSBasicGrenade()
{
	static ConstructorHelpers::FObjectFinder<UTPSSpAttackSkillData> DataRef(TEXT("/Game/TPSProject/EquipmentInfo/SpAttack/BasicGrenadeData.BasicGrenadeData"));
	if (DataRef.Object)
	{
		SkillData = DataRef.Object;
	}

	SetSkillContextFromData();
}
