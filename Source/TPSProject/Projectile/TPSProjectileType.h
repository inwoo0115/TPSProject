// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	RifleBullet UMETA(DisplayName = "Rifle Bullet"),
	RifleLaser UMETA(DisplayName = "Rifle Laser")
};
