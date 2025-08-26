// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSGameInstance.h"
#include "TPSSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GameData/TPSAbilityData.h"
#include "GameData/TPSEquipmentData.h"
#include "Item/TPSAbilityItem.h"

UTPSGameInstance::UTPSGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_AbilityData(
		TEXT("/Game/TPSProject/GameData/TPSAbilityDataTable.TPSAbilityDataTable"));
	if (DT_AbilityData.Succeeded())
	{
		AbilityDataTable = DT_AbilityData.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_EquipmentData(
		TEXT("/Game/TPSProject/GameData/TPSEquipmentDataTable.TPSEquipmentDataTable"));
	if (DT_EquipmentData.Succeeded())
	{
		EquipmentDataTable = DT_EquipmentData.Object;
	}
}

void UTPSGameInstance::Init()
{
	Super::Init();
	
	// 인벤토리 데이터 로드
	LoadPlayerData();
}

void UTPSGameInstance::LoadPlayerData()
{
	if (!UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSaveSlot"), 0))
	{
		// 임시 디폴트 장비/인벤토리 생성
		UTPSSaveGame* SaveGameInstance = Cast<UTPSSaveGame>(UGameplayStatics::CreateSaveGameObject(UTPSSaveGame::StaticClass()));

		SaveGameInstance->EquippedWeapon = TEXT("Weapon_00");
		SaveGameInstance->EquippedSpAttack = TEXT("SpAttack_00");
		SaveGameInstance->EquippedUlti = TEXT("Ultimate_00");
		SaveGameInstance->EquippedDrone = TEXT("Drone_00");

		TArray<FString> Abilities;
		Abilities.Add(TEXT("Rifle_00"));
		Abilities.Add(TEXT("Rifle_01"));
		Abilities.Add(TEXT("Rifle_02"));
		Abilities.Add(TEXT("Rifle_03"));
		Abilities.Add(TEXT("Rifle_04"));
		Abilities.Add(TEXT("Rifle_05"));
		Abilities.Add(TEXT("Ulti_00"));
		Abilities.Add(TEXT("Ulti_01"));
		Abilities.Add(TEXT("Ulti_02"));
		Abilities.Add(TEXT("Ulti_03"));
		Abilities.Add(TEXT("Ulti_04"));
		Abilities.Add(TEXT("Ulti_05"));
		Abilities.Add(TEXT("SpAttack_00"));
		Abilities.Add(TEXT("SpAttack_01"));
		Abilities.Add(TEXT("SpAttack_02"));
		Abilities.Add(TEXT("SpAttack_03"));
		Abilities.Add(TEXT("SpAttack_04"));
		Abilities.Add(TEXT("SpAttack_05"));
		Abilities.Add(TEXT("Drone_00"));
		Abilities.Add(TEXT("Drone_01"));
		Abilities.Add(TEXT("Drone_02"));
		Abilities.Add(TEXT("Drone_03"));
		Abilities.Add(TEXT("Drone_04"));
		Abilities.Add(TEXT("Drone_05"));

		SaveGameInstance->InventoryItems = Abilities;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("PlayerSaveSlot"), 0);
	}

	// Save file에서 데이터 추출
	LoadDataFromSave();
}

void UTPSGameInstance::LoadDataFromSave()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0);
	UTPSSaveGame* LoadedData = Cast<UTPSSaveGame>(LoadedGame);

	if (LoadedData && EquipmentDataTable)
	{
		FTPSEquipmentData* Weapon = EquipmentDataTable->FindRow<FTPSEquipmentData>(FName(*LoadedData->EquippedWeapon), TEXT(""));
		if (Weapon && Weapon->EquipmentClass)
		{
			WeaponClass = Weapon->EquipmentClass;
		}

		FTPSEquipmentData* SpAttack = EquipmentDataTable->FindRow<FTPSEquipmentData>(FName(*LoadedData->EquippedSpAttack), TEXT(""));
		if (SpAttack && SpAttack->EquipmentClass)
		{
			SpAttackSkillEquipmentClass = SpAttack->EquipmentClass;
		}

		FTPSEquipmentData* Ultimate = EquipmentDataTable->FindRow<FTPSEquipmentData>(FName(*LoadedData->EquippedUlti), TEXT(""));
		if (Ultimate && Ultimate->EquipmentClass)
		{
			UltimateSkillEquipmentClass = Ultimate->EquipmentClass;
		}

		FTPSEquipmentData* Drone = EquipmentDataTable->FindRow<FTPSEquipmentData>(FName(*LoadedData->EquippedDrone), TEXT(""));
		if (Drone && Drone->EquipmentClass)
		{
			DroneSkillEquipmentClass = Drone->EquipmentClass;
		}
	}

	if (LoadedData && AbilityDataTable)
	{
		TArray<FName> RowNames = AbilityDataTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FTPSAbilityData* ABData = AbilityDataTable->FindRow<FTPSAbilityData>(RowName, TEXT(""));
			if (ABData)
			{
				UTPSAbilityItem* NewItem = NewObject<UTPSAbilityItem>(this, UTPSAbilityItem::StaticClass());
				NewItem->InitItem(RowName, ABData->AbilityClass);
				AbilityInventory.Add(NewItem);
			}
		}
	}
}
