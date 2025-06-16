// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSBasicGrenade.h"
#include "TPSSpAttackSkillData.h"

ATPSBasicGrenade::ATPSBasicGrenade()
{
	static ConstructorHelpers::FObjectFinder<UTPSSpAttackSkillData> DataRef(TEXT("/Game/TPSProject/EquipmentInfo/SpAttack/BasicGrenadeData.BasicGrenadeData"));
	if (DataRef.Object)
	{
		SkillData = DataRef.Object;
	}

	SetSkillContextFromData();
}
