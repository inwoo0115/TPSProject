// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/TPSPlayerController.h"
#include "Interface/TPSSetTargetInterface.h"
#include "TPSMultiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSMultiPlayerController : public ATPSPlayerController, public ITPSSetTargetInterface
{
	GENERATED_BODY()

public:
	ATPSMultiPlayerController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void SetTarget(AActor* NewTarget) override;

	UPROPERTY()
	TObjectPtr<AActor> CurrentTarget;

	UFUNCTION(Client, Reliable)
	void ClientUpdateTarget(AActor* Target);  // 클라이언트 RPC

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UTPSHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UTPSHUDWidget> HUDWidget;
};
