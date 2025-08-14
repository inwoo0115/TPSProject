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


	bAllowStrafe = true;
}

void ATPSAIController::StartCustomTurnTo(FRotator TargetRotation)
{
    DesiredControlRotation = TargetRotation;
    bIsCustomTurning = true;
}

void ATPSAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn)
    {
        return;
    }

    FRotator CurrentRotation = ControlledPawn->GetActorRotation();

    FRotator TargetRotation = GetControlRotation();
    TargetRotation.Pitch = 0.f;
    TargetRotation.Roll = 0.f;

    const float RotationInterpSpeed = 0.1f;

    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, RotationInterpSpeed);

    ControlledPawn->SetActorRotation(NewRotation);
  
}

void ATPSAIController::StopBehaviorTree()
{
    if (BossBehaviorTree)
    {
        UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
        if (BTComp)
        {
            BTComp->StopTree();
        }
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
