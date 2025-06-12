// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TPSProjectileBase.h"
#include "TPSProjectileType.h"
#include "TPSProjectileListData.generated.h"



/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSProjectileListData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = ProjectileList)
	TMap<EProjectileType, TSubclassOf<ATPSProjectileBase>> ProjectileList;
};
