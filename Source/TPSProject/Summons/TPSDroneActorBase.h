// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TPSUltiGaugeInterface.h"
#include "TPSDroneActorBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSDroneActorBase : public AActor, public ITPSUltiGaugeInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSDroneActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle OverlapCheckTimerHandle;

	virtual void CheckOverlaps();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Owner를 제외하고 나머지 Replication
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

	virtual float GetUltimateGaugeRatio() override;

	// 콜리전 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> Collision;

	// 메쉬 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float Power = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float OverlapRatio = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float UltiGaugeRatio = 0.8f;

	// 상승 이동 관련 설정
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RiseDuration = 1.0f;

	FVector StartLocation;

	FVector TargetLocation;

	float RiseElapsedTime = 0.0f;

	bool bIsRising = true;

};
