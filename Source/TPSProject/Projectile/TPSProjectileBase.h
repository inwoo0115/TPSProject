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

	// Owner�� �����ϰ� ������ Replication
	// virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

protected:
	// �ݸ��� ������Ʈ
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TObjectPtr<class USphereComponent> Collision;


	// �߻�ü ������Ʈ
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileMovement")
	TObjectPtr<class UProjectileMovementComponent> Movement;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LifeTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float Damage = 10.0f;
};
