// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TPSAIController.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATPSAIController(const FObjectInitializer& ObjectInitializer);

	void StartCustomTurnTo(FRotator TargetRotation);

	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BossBehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBlackboardComponent* BlackboardComponent;

	//virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

	UPROPERTY()
	bool bIsCustomTurning = false;

	UPROPERTY()
	FRotator DesiredControlRotation;
};
