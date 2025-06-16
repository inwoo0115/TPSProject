// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSBasicDrone.h"
#include "TPSDroneSkillData.h"

ATPSBasicDrone::ATPSBasicDrone()
{
	static ConstructorHelpers::FObjectFinder<UTPSDroneSkillData> DataRef(TEXT("/Game/TPSProject/EquipmentInfo/Drone/BasicDroneData.BasicDroneData"));
	if (DataRef.Object)
	{
		SkillData = DataRef.Object;
	}

	SetSkillContextFromData();
}
