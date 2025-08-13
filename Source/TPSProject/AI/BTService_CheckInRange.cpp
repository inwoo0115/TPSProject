// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckInRange.h"
#include "BTService_CheckInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSAIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UBTService_CheckInRange::UBTService_CheckInRange(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("CheckInRange");
	Interval = 1.0f;
}

void UBTService_CheckInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TEXT("TargetActor")));
	if (!TargetActor) return;

	FName SocketName = TEXT("Muzzle_01");
	FVector StartLocation;
	if (USkeletalMeshComponent* MeshComp = OwnerPawn->FindComponentByClass<USkeletalMeshComponent>())
	{
		StartLocation = MeshComp->GetSocketLocation(SocketName);
	}
	else
	{
		StartLocation = OwnerPawn->GetActorLocation();
	}

	FVector EndLocation = TargetActor->GetActorLocation();

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerPawn);
	Params.bReturnPhysicalMaterial = false;

	bool bHit = World->LineTraceSingleByProfile(
		HitResult,
		StartLocation,
		EndLocation,
		TEXT("ProjectileProfile"),
		Params
	);

	FColor LineColor = bHit ? FColor::Red : FColor::Green;
	DrawDebugLine(World, StartLocation, EndLocation, LineColor, false, 1.0f, 0, 2.0f);

	bool bHasLineOfSight = false;

	if (bHit && HitResult.GetActor() == TargetActor)
	{
		bHasLineOfSight = true;
	}

	BBComp->SetValueAsBool(TEXT("IsOnSight"), bHasLineOfSight);
}
