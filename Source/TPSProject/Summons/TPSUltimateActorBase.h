// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSUltimateActorBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSUltimateActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSUltimateActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, Category = "VFX")
	TObjectPtr<class UNiagaraSystem> ExplosionEffect;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 3.0f;

	// 콜리전 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> Collision;
};
