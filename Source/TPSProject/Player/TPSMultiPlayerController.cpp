// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSMultiPlayerController.h"
#include "Character/TPSCharacterBase.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "GameInstance/TPSGameInstance.h"
#include "Widget/TPSHUDWidget.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Character/TPSNonCharacterBase.h"
#include "Item/TPSAbilityItem.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"


ATPSMultiPlayerController::ATPSMultiPlayerController()
{
	static ConstructorHelpers::FClassFinder<UTPSHUDWidget> HUDWidgetRef(TEXT("/Game/TPSProject/Widget/WB_HUD.WB_HUD_C"));
	if (HUDWidgetRef.Class)
	{
		HUDWidgetClass = HUDWidgetRef.Class;
	}
}

void ATPSMultiPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
	{
		return;
	}

	ATPSCharacterBase* PlayerCharacter = Cast<ATPSCharacterBase>(InPawn);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetCharacterControlData(ECharacterControlType::Combat);
	}
}

void ATPSMultiPlayerController::SetTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;

	ClientUpdateTarget(NewTarget);
}

void ATPSMultiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		UTPSHUDWidget* HUD = CreateWidget<UTPSHUDWidget>(this, HUDWidgetClass);
		if (HUD)
		{
			HUD->AddToViewport(5);
			HUD->SetVisibility(ESlateVisibility::Visible);
		}

		// 로컬 특성 설정
		UTPSGameInstance* GI = Cast<UTPSGameInstance>(GetGameInstance());
		if (GI)
		{
			WeaponAbilityList = GI->WeaponAbilityList;
			DroneAbilityList = GI->DroneAbilityList;
			SpAttackAbilityList = GI->SpAttackAbilityList;
			UltimateAbilityList = GI->UltimateAbilityList;
		}

		// Server RPC
		TArray<EAbilityType> WeaponKeys, DroneKeys, SpAttackKeys, UltimateKeys;
		TArray<TSubclassOf<UTPSEquipmentAbilityBase>> WeaponValues, DroneValues, SpAttackValues, UltimateValues;

		SerializeDataFromList(WeaponAbilityList, WeaponKeys, WeaponValues);
		SerializeDataFromList(DroneAbilityList, DroneKeys, DroneValues);
		SerializeDataFromList(SpAttackAbilityList, SpAttackKeys, SpAttackValues);
		SerializeDataFromList(UltimateAbilityList, UltimateKeys, UltimateValues);

		ServerInitializeAbilityList(WeaponKeys, WeaponValues,
			DroneKeys, DroneValues,
			SpAttackKeys, SpAttackValues,
			UltimateKeys, UltimateValues);
	}
}

void ATPSMultiPlayerController::SerializeDataFromList(
	TMap<EAbilityType, TObjectPtr<UTPSAbilityItem>>& List,
	TArray<EAbilityType>& OutKeys,
	TArray<TSubclassOf<UTPSEquipmentAbilityBase>>& OutValues)
{
	OutKeys.Empty();
	OutValues.Empty();

	for (const TPair<EAbilityType, TObjectPtr<UTPSAbilityItem>>& Pair : List)
	{
		if (Pair.Value)
		{
			OutKeys.Add(Pair.Key);
			OutValues.Add(Pair.Value->AbilityClass);
		}
	}
}

void ATPSMultiPlayerController::ServerInitializeAbilityList_Implementation(
	const TArray<EAbilityType>& WeaponKeys,
	const TArray<TSubclassOf<UTPSEquipmentAbilityBase>>& WeaponValues,
	const TArray<EAbilityType>& DroneKeys,
	const TArray<TSubclassOf<UTPSEquipmentAbilityBase>>& DroneValues,
	const TArray<EAbilityType>& SpAttackKeys,
	const TArray<TSubclassOf<UTPSEquipmentAbilityBase>>& SpAttackValues,
	const TArray<EAbilityType>& UltimateKeys,
	const TArray<TSubclassOf<UTPSEquipmentAbilityBase>>& UltimateValues)
{
	WeaponAbilityList.Empty();
	DroneAbilityList.Empty();
	SpAttackAbilityList.Empty();
	UltimateAbilityList.Empty();

	auto PopulateAbilityList = [this](const TArray<EAbilityType>& Keys,
		const TArray<TSubclassOf<UTPSEquipmentAbilityBase>>& Values,
		TMap<EAbilityType, TObjectPtr<UTPSAbilityItem>>& Dest)
		{
			int32 Count = FMath::Min(Keys.Num(), Values.Num());
			for (int32 i = 0; i < Count; ++i)
			{
				if (Values[i])
				{
					const UTPSEquipmentAbilityBase* DefaultObj = Values[i]->GetDefaultObject<UTPSEquipmentAbilityBase>();
					if (DefaultObj)
					{
						UTPSAbilityItem* NewItem = NewObject<UTPSAbilityItem>(this);
						NewItem->InitItem(FName(*DefaultObj->AbilityName.ToString()), Values[i]);
						Dest.Add(Keys[i], NewItem);
					}
				}
			}
		};

	PopulateAbilityList(WeaponKeys, WeaponValues, WeaponAbilityList);
	PopulateAbilityList(DroneKeys, DroneValues, DroneAbilityList);
	PopulateAbilityList(SpAttackKeys, SpAttackValues, SpAttackAbilityList);
	PopulateAbilityList(UltimateKeys, UltimateValues, UltimateAbilityList);
}

void ATPSMultiPlayerController::ClientUpdateTarget_Implementation(AActor* Target)
{
	auto TargetCharacter = Cast<ATPSNonCharacterBase>(Target);
	if (TargetCharacter)
	{
		auto EventSystem = GetGameInstance()->GetSubsystem<UTPSGameplayEventSubsystem>();
		if (EventSystem)
		{
			EventSystem->OnTargetHPChange.Broadcast(TargetCharacter->CurrentHp, TargetCharacter->MaxHp);
			EventSystem->OnTargetNameChange.Broadcast(TargetCharacter->CharacterName);
		}
	}
}
