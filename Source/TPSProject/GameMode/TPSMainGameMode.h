// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPSMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATPSMainGameMode();

	void StartPlay() override;
};
