// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* WeaponInfo;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* SpAttackInfo;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* UltimateInfo;

	UPROPERTY(meta = (BindWidget))
	class UTPSEquipmentInfoWidget* DroneInfo;

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseWindowButton;

	UPROPERTY(meta = (BindWidget))
	class UGridPanel* InventoryGrid;

	UFUNCTION()
	void OnCloseWindowClicked();

	UFUNCTION()
	void UpdateEquipmentInfo();

	UFUNCTION()
	void UpdateInventoryInfo();

	UFUNCTION()
	void InitializeWidget(ESlateVisibility NewVisibility);


protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<class UTPSInventoryItemWidget> InventoryItemWidgetClass;

	UFUNCTION()
	void HandleItemClicked(class UTPSInventoryItemWidget* Item); 
};
