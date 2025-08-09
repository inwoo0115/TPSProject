// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckInRange.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UBTService_CheckInRange : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckInRange(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
