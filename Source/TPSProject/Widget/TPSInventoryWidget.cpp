// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSInventoryWidget.h"
#include "Components/Button.h"
#include "Character/TPSCharacterBase.h"
#include "TPSEquipmentInfoWidget.h"

void UTPSInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseWindowButton)
		CloseWindowButton->OnClicked.AddDynamic(this, &UTPSInventoryWidget::OnCloseWindowClicked);

	OnVisibilityChanged.AddDynamic(this, &UTPSInventoryWidget::InitializeWidget);

}

void UTPSInventoryWidget::OnCloseWindowClicked()
{
	RemoveFromParent();
}

void UTPSInventoryWidget::UpdateEquipmentInfo()
{
	if (WeaponInfo)
	{
		WeaponInfo->InitializeWeaponInfo();
	}

	if (DroneInfo)
	{
		DroneInfo->InitializeDroneInfo();
	}

	if (SpAttackInfo)
	{
		SpAttackInfo->InitializeSpAttackInfo();
	}

	if (UltimateInfo)
	{
		UltimateInfo->InitializeUltimateInfo();
	}
}

void UTPSInventoryWidget::UpdateInventoryInfo()
{
	// Game Instance에서 아이템 (어빌리티, 텍스트, 이미지) 배열을 불러와서 Grid Panel 자식으로 추가

	if (!InventoryGrid)
	{
		return;
	}
}


void UTPSInventoryWidget::InitializeWidget(ESlateVisibility NewVisibility)
{
	if (NewVisibility != ESlateVisibility::Visible)
	{
		return;
	}

	// 장비 업데이트
	UpdateEquipmentInfo();

	// 인벤토리 업데이트
	UpdateInventoryInfo();
}
