// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "TPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTPSGameInstance();

	virtual void Init() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSWeaponBase> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSDroneSkillBase> DroneSkillEquipmentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSSpAttackSkillBase> SpAttackSkillEquipmentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ATPSUltimateSkillBase> UltimateSkillEquipmentClass;

	void LoadPlayerData();

	void LoadDataFromSave();

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* EquipmentDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	UDataTable* AbilityDataTable;

	// 개인 인벤토리
	TArray<class UTPSAbilityItem*> AbilityInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> WeaponAbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> DroneAbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> SpAttackAbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> UltimateAbilityList;
};
