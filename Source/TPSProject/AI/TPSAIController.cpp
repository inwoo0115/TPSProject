// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TPSAIController.h"
#include "BehaviorTree/BehaviorTree.h"

ATPSAIController::ATPSAIController(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAsset(TEXT("/Game/TPSProject/AI/BT_BossAI.BT_BossAI"));
	if (BehaviorTreeAsset.Object)
	{
		BossBehaviorTree = BehaviorTreeAsset.Object;
	}
}

void ATPSAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BossBehaviorTree)
	{
		RunBehaviorTree(BossBehaviorTree);
	}
}
