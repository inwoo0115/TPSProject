// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CastSkill.h"

UBTTask_CastSkill::UBTTask_CastSkill(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Cast Skill");

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CastSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTask_CastSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
