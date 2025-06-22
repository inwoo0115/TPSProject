// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "Projectile/TPSProjectileType.h"
#include "TPSSpAttackSkillBase.generated.h"


USTRUCT(BlueprintType)
struct FSpAttackSkillContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UltiGaugeRatio = 0.0f;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	float ExplosionRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillEquipmentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProjectileType CurrentProjectile = EProjectileType::BasicGrenade;
};

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSSpAttackSkillBase : public ATPSAbilityEquipmentBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void CastSkill();

	virtual void LaunchSkill();
	
	virtual bool GetCanCast();

	void SetSkillContextFromData();

	virtual void InitializeAbilities() override;

	// 스킬 장비 정보 데이터 에셋
	UPROPERTY(Replicated)
	TObjectPtr<class UTPSSpAttackSkillData> SkillData;


	UPROPERTY(Replicated)
	bool bCanCast = true;

	UFUNCTION(BlueprintCallable)
	FSpAttackSkillContext GetSkillContext() const;

	// 수류탄 클래스 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> ProjectileList;

	virtual void ChangeFieldStatByValue(FName FieldName, float Value) override;

	float CurrentCoolTime = 0.0f;
protected:

	FTimerHandle CastCooldownHandle;

	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "SkillEquipment")
	FSpAttackSkillContext SkillContext;

};
