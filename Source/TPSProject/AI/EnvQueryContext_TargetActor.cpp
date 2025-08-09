// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnvQueryContext_TargetActor.h"
#include "EnvQueryContext_TargetActor.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "GameFramework/Actor.h"
#include "AISystem.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "TPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UEnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	ATPSAIController* AIController = Cast<ATPSAIController>(QueryOwner->GetInstigatorController());
	UBlackboardComponent* BlackboardComp = AIController ? AIController->GetBlackboardComponent() : nullptr;
    if (BlackboardComp)
    {
        AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
		if (TargetActor)
		{
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
			return;
		}
    }
	else
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, nullptr);
	}
}
