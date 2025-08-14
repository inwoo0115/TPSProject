// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Attack(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void Fire(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:
	TSubclassOf<class ATPSProjectileBase> DefaultProjectile;

	float AttackCoolTime = 0.0f;

	float AttackContinueTime = 3.0f;
};
