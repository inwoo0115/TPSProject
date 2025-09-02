// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "Summons/TPSDroneType.h"
#include "TPSDroneSkillBase.generated.h"


USTRUCT(BlueprintType)
struct FDroneSkillContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UltiGaugeRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LifeTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> SkillEquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SkillEquipmentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDroneType CurrentDroneActor = EDroneType::BasicDrone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf <class ATPSSkillRangeDecalBase> RangeDecal;
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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void ShowUI();

	virtual void CastSkill();

	virtual void LaunchSkill();

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

	// 드론 클래스 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDroneType, TSubclassOf<class ATPSDroneActorBase>> DroneActorList;

	// 스킬 범위 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ATPSSkillRangeDecalBase> TargetRange;

	virtual void ChangeFieldStatByValue(FName FieldName, float Value) override;

	UPROPERTY()
	float CurrentCoolTime = 0.0f;


	// 현재 장착 중인 특성 불러오기
	virtual void InitializeAbilityListFromInventory() override;

protected:
	FTimerHandle CastCooldownHandle;

	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "SkillEquipment")
	FDroneSkillContext SkillContext;
};
