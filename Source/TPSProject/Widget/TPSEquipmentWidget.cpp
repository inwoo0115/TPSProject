// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentWidget.h"
#include "Components/Button.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "TPSMainWeaponSettingWidget.h"
#include "TPSDroneSettingWidget.h"
#include "TPSUltimateSettingWidget.h"
#include "TPSSpAttackSettingWidget.h"

void UTPSEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackArrow)
	{
		BackArrow->OnClicked.AddDynamic(this, &UTPSEquipmentWidget::OnBackArrowButtonClicked);
	}

	if (Weapon01)
	{
		Weapon01->OnClicked.AddDynamic(this, &UTPSEquipmentWidget::OnWeapon01Clicked);
	}

	if (Weapon02)
	{
		Weapon02->OnClicked.AddDynamic(this, &UTPSEquipmentWidget::OnWeapon02Clicked);
	}

	if (SpWeapon)
	{
		SpWeapon->OnClicked.AddDynamic(this, &UTPSEquipmentWidget::OnSpWeaponClicked);
	}

	if (Ultimate)
	{
		Ultimate->OnClicked.AddDynamic(this, &UTPSEquipmentWidget::OnUltimateClicked);
	}

	if (Drone)
	{
		Drone->OnClicked.AddDynamic(this, &UTPSEquipmentWidget::OnDroneClicked);
	}
}

void UTPSEquipmentWidget::OnBackArrowButtonClicked()
{
    auto UIsubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
    if (UIsubsystem)
    {
        UIsubsystem->HideCurrentUI();
    }
}

void UTPSEquipmentWidget::OnWeapon01Clicked()
{
	if (MainWeaponSettingWidgetClass)
	{
		// ���� ����
		UTPSMainWeaponSettingWidget* Widget = CreateWidget<UTPSMainWeaponSettingWidget>(GetWorld(), MainWeaponSettingWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport(12);
		}
	}
}

void UTPSEquipmentWidget::OnWeapon02Clicked()
{
	// �ι��� ���� ���� �� �߰�
}

void UTPSEquipmentWidget::OnSpWeaponClicked()
{
	if (SpAttackSettingWidgetClass)
	{
		// ���� ����
		UTPSSpAttackSettingWidget* Widget = CreateWidget<UTPSSpAttackSettingWidget>(GetWorld(), SpAttackSettingWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport(12);
		}
	}
}

void UTPSEquipmentWidget::OnUltimateClicked()
{
	if (UltimateSettingWidgetClass)
	{
		// ���� ����
		UTPSUltimateSettingWidget* Widget = CreateWidget<UTPSUltimateSettingWidget>(GetWorld(), UltimateSettingWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport(12);
		}
	}
}

void UTPSEquipmentWidget::OnDroneClicked()
{
	if (DroneSettingWidgetClass)
	{
		// ���� ����
		UTPSDroneSettingWidget* Widget = CreateWidget<UTPSDroneSettingWidget>(GetWorld(),DroneSettingWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport(12);
		}
	}
}
