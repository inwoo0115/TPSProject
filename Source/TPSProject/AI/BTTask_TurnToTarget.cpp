// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "BTTask_TurnToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSAIController.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
	bNotifyTick = true; // Enable ticking for this task
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (nullptr == TargetPawn)
	{
		return EBTNodeResult::Failed;
	}

	float TurnSpeed = 3.0f;
	FVector LookVector = TargetPawn->GetActorLocation() - ControllingPawn->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();

	// Set focus on the target pawn
	ATPSAIController* AIController = Cast<ATPSAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AIController->StartCustomTurnTo(TargetRot);
		AIController->SetFocus(TargetPawn);
	}

	return EBTNodeResult::Succeeded;
}
