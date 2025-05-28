// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSMenuGameMode();

	virtual void BeginPlay() override;
};
