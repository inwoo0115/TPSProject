// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/TPSPlayerController.h"
#include "TPSMultiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSMultiPlayerController : public ATPSPlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	
};
