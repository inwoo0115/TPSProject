// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSDroneActorBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSDroneActorBase : public AActor
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

	// Owner�� �����ϰ� ������ Replication
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;


	// �ݸ��� ������Ʈ
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> Collision;

	// �޽� ������Ʈ
	UPROPERTY(EditDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.0f;

	// ��� �̵� ���� ����
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RiseDuration = 1.0f;

	FVector StartLocation;

	FVector TargetLocation;

	float RiseElapsedTime = 0.0f;

	bool bIsRising = true;

};
