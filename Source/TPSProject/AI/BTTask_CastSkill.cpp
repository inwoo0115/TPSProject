// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_CastSkill.h"
#include "TPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/TPSBossCharacter.h"
#include "Animation/TPSAnimMontageData.h"

UBTTask_CastSkill::UBTTask_CastSkill(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Cast Skill");

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_CastSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    if (BossCharacter->GetSkillCoolTime() >= 10.0f)
    {
        BossCharacter->CastSkill();

        return EBTNodeResult::InProgress;
    }
    else
    {
        return EBTNodeResult::Failed;
    }
}

void UBTTask_CastSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    ATPSAIController* AICon = Cast<ATPSAIController>(OwnerComp.GetAIOwner());
    if (!AICon) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

    APawn* ControlPawn = Cast<APawn>(AICon->GetPawn());
    if (!ControlPawn) FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

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
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        }
    }
}
