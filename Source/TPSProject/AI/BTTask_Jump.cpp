// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Jump.h"
#include "BTTask_Jump.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TPSAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Gameframework/CharacterMovementComponent.h"

UBTTask_Jump::UBTTask_Jump(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Jump to Location");

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Jump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ATPSAIController* AICon = Cast<ATPSAIController>(OwnerComp.GetAIOwner());
    if (!AICon) return EBTNodeResult::Failed;

    APawn* ControlPawn = Cast<APawn>(AICon->GetPawn());
    if (!ControlPawn) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return EBTNodeResult::Failed;

    FVector EndLocation = BB->GetValueAsVector(TEXT("MoveLocation"));
    FVector StartLocation = ControlPawn->GetActorLocation();

    FVector LaunchVelocity;

    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        LaunchVelocity,
        StartLocation,
        EndLocation,
        1000.f, // 발사 속도 (cm/s)
        true,  // 고각 해결책 사용 여부
        0.f,    // 충돌 반경
        0.f,    // 중력 오버라이드 (0이면 기본 중력 사용)
        ESuggestProjVelocityTraceOption::DoNotTrace
    );

    if (bHaveAimSolution && !bIsJumping)
    {
		ACharacter* ControlCharacter = Cast<ACharacter>(ControlPawn);
		ControlCharacter->LaunchCharacter(LaunchVelocity, true, true);
        bIsJumping = true;
        return EBTNodeResult::InProgress;
    }
    else
    {
		return EBTNodeResult::Failed;
    }
}

void UBTTask_Jump::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (!bIsJumping)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    ACharacter* MyChar = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (!MyChar)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (MyChar->GetCharacterMovement()->IsMovingOnGround())
    {
        bIsJumping = false;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
