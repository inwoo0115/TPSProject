// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "TPSEquipmentInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoSlotWidget* Slot1_1;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoSlotWidget* Slot1_2;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoSlotWidget* Slot2_1;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoSlotWidget* Slot2_2;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoSlotWidget* Slot3_1;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoSlotWidget* Slot3_2;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquipmentName;

	UPROPERTY(meta = (BindWidget))
	class UImage* EquipmentIcon;

	void InitializeWeaponInfo(class UTPSInventoryWidget* Inventory);

	void InitializeDroneInfo(class UTPSInventoryWidget* Inventory);

	void InitializeUltimateInfo(class UTPSInventoryWidget* Inventory);

	void InitializeSpAttackInfo(class UTPSInventoryWidget* Inventory);

	void UpdateWeaponInfoData();

	void UpdateDroneInfoData();

	void UpdateUltimateInfoData();

	void UpdateSpAttackInfoData();

	void AddSlotItemToData(TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>>& List, UTPSEquipmentInfoSlotWidget* InfoSlot, EAbilityType Type);

	void SetImageAndText(TSoftObjectPtr<UTexture2D> Icon, FText ContextName);

	void SetAbilities(TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> List, UTPSInventoryWidget* Inventory);

	void SetSlotColor(bool Active);

	void SetSlotType(EAbilityType AbilityType);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UTPSInventoryItemWidget> InventoryItemWidgetClass;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
