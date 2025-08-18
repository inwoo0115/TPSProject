// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/TPSProjectileBase.h"
#include "TPSHommingMissile.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSHommingMissile : public ATPSProjectileBase
{
	GENERATED_BODY()
	
public:
	ATPSHommingMissile();

	virtual void BeginPlay() override;

	void SetHomingTarget(USceneComponent* Target);

	FTimerHandle HomingTimerHandle;

	// À¯µµÅº °î·ü Ãß°¡
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing")
	float CurveDuration = 0.5f; // ·£´ý °î¼± Áö¼Ó ½Ã°£

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing")
	float CurveStrength = 200.f; // ¹æÇâ Èçµé¸² °­µµ

	FTimerHandle CurveTimerHandle;
	FVector RandomCurveOffset;

	void ApplyRandomCurve();

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	// Owner¸¦ Á¦¿ÜÇÏ°í ³ª¸ÓÁö Replication
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;


private:
	void EnableHoming();
	USceneComponent* TargetComponent;

	UPROPERTY(EditAnywhere, Category = "VFX")
	TObjectPtr<class UNiagaraSystem> ExplosionEffect;
};
