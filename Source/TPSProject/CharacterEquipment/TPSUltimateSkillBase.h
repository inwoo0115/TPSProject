// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "TPSUltimateSkillBase.generated.h"

USTRUCT(BlueprintType)
struct FUltimateSkillContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxGauge = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillEquipmentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf <class ATPSSkillRangeDecalBase> RangeDecal;
};


/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSUltimateSkillBase : public ATPSAbilityEquipmentBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void ShowUI();

	virtual void CastSkill();

	virtual void LaunchSkill();

	virtual bool GetCanCast();

	void ClearUpdateDelegate();

	void SetSkillContextFromData();

	virtual void InitializeAbilities() override;

	void UpdateGauge(float AddGauge);

	// ��ų ��� ���� ������ ����
	UPROPERTY(Replicated)
	TObjectPtr<class UTPSUltimateSkillData> SkillData;

	UFUNCTION(BlueprintCallable)
	FUltimateSkillContext GetSkillContext() const;

	// ��ų ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ATPSSkillRangeDecalBase> TargetRange;

protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "SkillEquipment")
	FUltimateSkillContext SkillContext;

	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing=OnRepGaugeChanged, EditAnywhere, BlueprintReadWrite)
	float CurrentGauge = 0.0f;

	UFUNCTION()
	void OnRepGaugeChanged();

	FDelegateHandle DelegateHandle;
};
