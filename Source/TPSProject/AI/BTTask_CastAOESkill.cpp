// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CastAOESkill.h"

UBTTask_CastAOESkill::UBTTask_CastAOESkill(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Cast AOE Skill");

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CastAOESkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

void UBTTask_CastAOESkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
