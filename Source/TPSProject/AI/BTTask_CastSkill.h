// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CastSkill.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTTask_CastSkill : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_CastSkill(const FObjectInitializer& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
