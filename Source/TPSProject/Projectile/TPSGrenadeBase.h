// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/TPSProjectileBase.h"
#include "TPSGrenadeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSGrenadeBase : public ATPSProjectileBase
{
	GENERATED_BODY()

public:
	ATPSGrenadeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	// 메쉬 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;
};