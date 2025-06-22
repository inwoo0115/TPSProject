// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSDroneType.generated.h"

UENUM(BlueprintType)
enum class EDroneType : uint8
{
	BasicDrone UMETA(DisplayName = "Basic Drone"),
	AttackDrone UMETA(DisplayName = "Attack Drone"),
	FootHolderDrone UMETA(DisplayName = "FootHolder Drone")
};

