// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TPSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, Category = "Player Data")
    FString EquippedWeapon;

    UPROPERTY(BlueprintReadWrite, Category = "Player Data")
    FString EquippedUlti;

    UPROPERTY(BlueprintReadWrite, Category = "Player Data")
    FString EquippedSpAttack;

    UPROPERTY(BlueprintReadWrite, Category = "Player Data")
    FString EquippedDrone;

    UPROPERTY(BlueprintReadWrite, Category = "Player Data")
    TArray<FString> InventoryItems;
};
