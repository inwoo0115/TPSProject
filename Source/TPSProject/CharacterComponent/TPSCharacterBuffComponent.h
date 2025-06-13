// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSCharacterBuffComponent.generated.h"

UENUM(BlueprintType)
enum class EBuffType : uint8
{
	All UMETA(DisplayName = "All"),
	Drone UMETA(DisplayName = "Drone"),
	SpAttack UMETA(DisplayName = "SpAttack"),
	Attack UMETA(DisplayName = "Attack"),
	Ulti UMETA(DisplayName = "Ulti"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSCharacterBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSCharacterBuffComponent();



protected:
	void GetBuffByField(FName FieldName, float& OutDamage);

		
};
