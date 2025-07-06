// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/TPSUltiGaugeInterface.h"
#include "TPSProjectileType.h"
#include "TPSProjectileBase.generated.h"


UCLASS()
class TPSPROJECT_API ATPSProjectileBase : public AActor, public ITPSUltiGaugeInterface
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

	virtual float GetUltimateGaugeRatio() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float UltiGaugeRatio = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float ExplosionRadius = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	EProjectileType ProjectileType = EProjectileType::None;

protected:
	// 콜리전 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> Collision;

	// 발사체 컴포넌트
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileMovement")
	TObjectPtr<class UProjectileMovementComponent> Movement;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LifeTime = 3.0f;
};
