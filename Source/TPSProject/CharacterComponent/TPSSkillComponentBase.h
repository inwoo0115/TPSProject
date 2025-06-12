// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSGameplayEventSystem.h"
#include "TPSSkillComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSSkillComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

};
