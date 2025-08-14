// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_LevelStart.h"
#include "BTTask_LevelStart.h"
#include "TPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/TPSBossCharacter.h"
#include "Animation/TPSAnimMontageData.h"


UBTTask_LevelStart::UBTTask_LevelStart(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Level Start");

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_LevelStart::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    ATPSAIController* AICon = Cast<ATPSAIController>(OwnerComp.GetAIOwner());
    if (!AICon) return EBTNodeResult::Failed;

    APawn* ControlPawn = Cast<APawn>(AICon->GetPawn());
    if (!ControlPawn) return EBTNodeResult::Failed;

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return EBTNodeResult::Failed;

    ATPSBossCharacter* BossCharacter = Cast<ATPSBossCharacter>(ControlPawn);
    if (!BossCharacter) return EBTNodeResult::Failed;

    if (bIsLevelStart)
    {
        return EBTNodeResult::Failed;
    }

    BossCharacter->PlayAnimMontage(BossCharacter->AnimMontageData->AnimMontages[EMontageType::LevelStart]);

    return EBTNodeResult::InProgress;
}

void UBTTask_LevelStart::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (bIsLevelStart)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    ATPSAIController* AICon = Cast<ATPSAIController>(OwnerComp.GetAIOwner());
    if (!AICon) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    APawn* ControlPawn = Cast<APawn>(AICon->GetPawn());
    if (!ControlPawn) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    if (!BB) return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    ATPSBossCharacter* BossCharacter = Cast<ATPSBossCharacter>(ControlPawn);
    if (!BossCharacter)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UAnimInstance* Instance = BossCharacter->GetMesh()->GetAnimInstance();
    if (Instance)
    {
        if (Instance->IsAnyMontagePlaying())
        {
            return;
        }
        else
        {
            bIsLevelStart = true;
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            BB->SetValueAsBool(TEXT("IsLevelStart"), true);
        }
    }
}
