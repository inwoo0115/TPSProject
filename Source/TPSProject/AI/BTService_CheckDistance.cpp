// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckDistance.h"
#include "BTService_CheckDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSAIController.h"

UBTService_CheckDistance::UBTService_CheckDistance()
{
	NodeName = TEXT("CheckDistance");
	Interval = 1.0f;
}

void UBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerPawn == nullptr)
	{
		return;
	}

	FVector OwnerLocation = OwnerPawn->GetActorLocation();
	UWorld* World = OwnerPawn->GetWorld();
	if (World == nullptr)
	{
		return;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp) return;

	FVector MoveLocation = BBComp->GetValueAsVector(TEXT("MoveLocation"));
	FVector ActorLocation = OwnerPawn->GetActorLocation();

	float Distance = FVector::Dist(OwnerLocation, MoveLocation);

	if (Distance < 1000.0f)
	{
		BBComp->SetValueAsBool(TEXT("IsJumpDistance"), false);
	}
	else
	{
		BBComp->SetValueAsBool(TEXT("IsJumpDistance"), true);
	}
}
