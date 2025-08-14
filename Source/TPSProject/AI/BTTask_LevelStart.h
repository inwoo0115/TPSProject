// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LevelStart.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTTask_LevelStart : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_LevelStart(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	bool bIsLevelStart = false;
};
