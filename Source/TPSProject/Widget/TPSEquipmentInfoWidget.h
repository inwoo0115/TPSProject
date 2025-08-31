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

	void InitializeWeaponInfo();

	void InitializeDroneInfo();

	void InitializeUltimateInfo();

	void InitializeSpAttackInfo();

	void SetImageAndText(TSoftObjectPtr<UTexture2D> Icon, FText ContextName);

	void SetAbilities(TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> List);

	void SetSlotColor(bool Active);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UTPSInventoryItemWidget> InventoryItemWidgetClass;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
