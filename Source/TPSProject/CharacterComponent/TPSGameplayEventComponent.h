// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSGameplayEventComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSGameplayEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSGameplayEventComponent();

	// Attack Event
	FOnHitEvent OnHitEvent;

};
