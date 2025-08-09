// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSAIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	float SearchRadius = 5000.0f;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerPawn); // 자기 자신 무시

	bool bOverlap = World->OverlapMultiByObjectType(
		OverlapResults,
		OwnerLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn), // Pawn만 검색
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams
	);
	
	DrawDebugSphere(
		World,
		OwnerLocation,
		SearchRadius,
		16,             // 세그먼트 수
		FColor::Green,  // 색상
		false,          // 영구 표시 여부(false면 일정 시간 후 사라짐)
		0.5f            // 표시 지속 시간
	);

	if (bOverlap)
	{
		TArray<APawn*> Candidates;
		for (auto& Result : OverlapResults)
		{
			APawn* FoundPawn = Cast<APawn>(Result.GetActor());
			if (FoundPawn)
			{
				Candidates.Add(FoundPawn);
			}
		}

		if (Candidates.Num() > 0)
		{
			int32 RandomIndex = FMath::RandRange(0, Candidates.Num() - 1);
			APawn* ChosenPawn = Candidates[RandomIndex];

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), ChosenPawn);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
	}
}
