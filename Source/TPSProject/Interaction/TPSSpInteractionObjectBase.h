// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TPSSpInteractionObjectBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSSpInteractionObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSSpInteractionObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> InteractionBox;

	void TraceBeginOverlap(AController* PC);

	void TraceEndOverlap(AController* PC);
};
