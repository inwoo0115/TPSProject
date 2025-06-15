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
	ATPSMultiPlayerController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

protected:
	// HUD Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UTPSHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UTPSHUDWidget> HUDWidget;
};
