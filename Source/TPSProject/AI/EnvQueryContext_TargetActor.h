// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvQueryContext_TargetActor.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UEnvQueryContext_TargetActor : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
