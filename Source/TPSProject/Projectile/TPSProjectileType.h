// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	None UMETA(DisplayName = "None"),

	// Rifle Bullet
	BasicBullet UMETA(DisplayName = "Basic Bullet"),
	LaserBullet UMETA(DisplayName = "Laser Bullet"),
	FireBullet UMETA(DisplayName = "Fire Bullet"),
	EnergyBullet UMETA(DisplayName = "Energy Bullet"),

	// Grenade
	BasicGrenade UMETA(DisplayName = "Basic Grenade"),
	FlameGrenade UMETA(DisplayName = "Flame Grenade"),
	HealGrenade  UMETA(DisplayName = "Heal Grenade")
};
