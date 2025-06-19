// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSProjectileBase.generated.h"


UCLASS()
class TPSPROJECT_API ATPSProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATPSProjectileBase();

protected:
	virtual void BeginPlay() override;


	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	

	virtual void SetDamage(float NewDamage);

	// Owner를 제외하고 나머지 Replication
	// virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

protected:
	// 콜리전 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> Collision;


	// 발사체 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileMovement")
	TObjectPtr<class UProjectileMovementComponent> Movement;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LifeTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float Damage = 10.0f;
};
