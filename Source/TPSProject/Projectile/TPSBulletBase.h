// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/TPSProjectileBase.h"
#include "TPSBulletBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSBulletBase : public ATPSProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATPSBulletBase();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	// Owner를 제외하고 나머지 Replication
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;


protected:
	// 메쉬 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "StaticMesh")
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
