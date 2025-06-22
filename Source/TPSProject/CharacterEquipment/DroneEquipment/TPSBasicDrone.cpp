// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSBasicDrone.h"
#include "CharacterEquipment/TPSDroneSkillData.h"

ATPSBasicDrone::ATPSBasicDrone()
{
	static ConstructorHelpers::FObjectFinder<UTPSDroneSkillData> DataRef(TEXT("/Game/TPSProject/EquipmentInfo/Drone/BasicDroneData.BasicDroneData"));
	if (DataRef.Object)
	{
		SkillData = DataRef.Object;
	}

	SetSkillContextFromData();
}
