// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "TPSDroneSkillBase.generated.h"


USTRUCT(BlueprintType)
struct FDroneSkillContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UltiGaugeRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillEquipmentName;
};
/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSDroneSkillBase : public ATPSAbilityEquipmentBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void ShowUI();

	virtual void Cast();

	virtual void Launch();

	virtual bool GetCanCast();

	void SetSkillContextFromData();

	virtual void InitializeAbilities() override;

	// 스킬 장비 정보 데이터 에셋
	UPROPERTY(Replicated)
	TObjectPtr<class UTPSDroneSkillData> SkillData;

	UPROPERTY(Replicated)
	bool bCanCast = true;

	UFUNCTION(BlueprintCallable)
	FDroneSkillContext GetSkillContext() const;

protected:
	float CurrentCoolTime = 0.0f;

	FTimerHandle CastCooldownHandle;

	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "SkillEquipment")
	FDroneSkillContext SkillContext;
};
