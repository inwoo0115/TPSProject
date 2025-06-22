// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "Summons/TPSUltimateType.h"
#include "Summons/TPSUltimateActorBase.h"
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
	float LifeTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillEquipmentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf <class ATPSSkillRangeDecalBase> RangeDecal;

	UPROPERTY(EditAnywhere, Category = SkillInfo)
	EUltimateType CurrentUltimate;
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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ShowUI();

	virtual void CastSkill();

	virtual void LaunchSkill();

	virtual bool GetCanCast();

	virtual bool GetInRange();

	void ClearUpdateDelegate();

	void SetSkillContextFromData();

	void DeleteTargetUI();

	virtual void InitializeAbilities() override;

	void UpdateGauge(float AddGauge);

	// 스킬 장비 정보 데이터 에셋
	UPROPERTY(Replicated)
	TObjectPtr<class UTPSUltimateSkillData> SkillData;

	UFUNCTION(BlueprintCallable)
	FUltimateSkillContext GetSkillContext() const;

	// 스킬 범위 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ATPSSkillRangeDecalBase> TargetRange;

	UPROPERTY(EditAnywhere, Category = UltimateList)
	TMap<EUltimateType, TSubclassOf<ATPSUltimateActorBase>> UltimateActorList;

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

	UPROPERTY()
	FVector TargetLocation = FVector(0, 0, 0);

	UFUNCTION(Server, Reliable)
	void ServerRPCTargetLocation(FVector NewLocation);

	bool bIsInRange = false;
};
