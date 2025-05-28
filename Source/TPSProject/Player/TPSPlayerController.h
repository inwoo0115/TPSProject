// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/TPSInteractionWidgetInterface.h"
#include "TPSPlayerController.generated.h"


/**
 *
 */

USTRUCT()
struct FInteractionUIInfo
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* Widget = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY()
	bool bCanInteract = false;
};

UCLASS()
class TPSPROJECT_API ATPSPlayerController : public APlayerController, public ITPSInteractionWidgetInterface
{
	GENERATED_BODY()
	
public:
	ATPSPlayerController();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	// Interaction interface
	void SetCanInteract(EInteractionUIType UIType, bool NewInteract) override;

	bool GetCanInteract(EInteractionUIType UIType);

	TMap<EInteractionUIType, FInteractionUIInfo> InteractionUIManager;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TMap<EInteractionUIType, TSubclassOf<UUserWidget>> InteractionWidgetClasses;

	void ShowInteractionUI(EInteractionUIType UIType, AActor* TargetActor) override;

	void HideInteractionUI(EInteractionUIType UIType, AActor* TargetActor) override;
};
