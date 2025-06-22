// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSBasicUltimate.h"
#include "CharacterEquipment/TPSUltimateSkillData.h"

ATPSBasicUltimate::ATPSBasicUltimate()
{
	// Basic Rifle Data
	static ConstructorHelpers::FObjectFinder<UTPSUltimateSkillData> DataRef(TEXT("/Game/TPSProject/EquipmentInfo/Ultimate/BasicUltimate.BasicUltimate"));
	if (DataRef.Object)
	{
		SkillData = DataRef.Object;
	}

	// 데이터 초기화
	SetSkillContextFromData();
}
