// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/TPSProjectileBase.h"
#include "TPSRifleBullet.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSRifleBullet : public ATPSProjectileBase
{
	GENERATED_BODY()
	
public:
	ATPSRifleBullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;


protected:
	// 메쉬 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
