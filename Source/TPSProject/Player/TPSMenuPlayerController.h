// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
};
