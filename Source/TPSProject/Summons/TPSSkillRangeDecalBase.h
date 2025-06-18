// Fill out your copyright notice in the Descripton page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSSkillRangeDecalBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSSkillRangeDecalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSSkillRangeDecalBase();

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
	TObjectPtr<class UDecalComponent> RangeDecal;
};
