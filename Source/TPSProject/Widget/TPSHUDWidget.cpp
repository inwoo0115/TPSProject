// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"

void UTPSHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto EventSystem = GetGameInstance()->GetSubsystem<UTPSGameplayEventSubsystem>();
	if (EventSystem)
	{
		EventSystem->OnHPChange.AddUObject(this, &UTPSHUDWidget::UpdateHP);
		EventSystem->OnAmmoChange.AddUObject(this, &UTPSHUDWidget::UpdateAmmo);
		EventSystem->OnUltimateGaugeChange.AddUObject(this, &UTPSHUDWidget::UpdateUltimate);
		EventSystem->OnSpAttackCoolTimeChange.AddUObject(this, &UTPSHUDWidget::UpdateSpAttack);
		EventSystem->OnDroneCoolTimeChange.AddUObject(this, &UTPSHUDWidget::UpdateDrone);

		EventSystem->OnTargetNameChange.AddUObject(this, &UTPSHUDWidget::UpdateTargetName);
		EventSystem->OnTargetHPChange.AddUObject(this, &UTPSHUDWidget::UpdateTargetHP);
	}

	HideTargetHPBar();
	HideTargetName();
}

void UTPSHUDWidget::UpdateHP(int32 CurrentHPValue, int32 MaxHPValue)
{
	if (CurrentHP)
	{
		CurrentHP->SetText(FText::AsNumber(CurrentHPValue));
	}
	
	if (MaxHP)
	{
		MaxHP->SetText(FText::AsNumber(MaxHPValue));
	}

	if (HPBar)
	{
		float HPPercent = float(CurrentHPValue) / float(MaxHPValue);
		HPBar->SetPercent(HPPercent);
	}
}

void UTPSHUDWidget::UpdateAmmo(int32 CurrentAmmoValue, int32 MaxAmmoValue)
{
	if (CurrentAmmo)
	{
		CurrentAmmo->SetText(FText::AsNumber(CurrentAmmoValue));
	}

	if (MaxAmmo)
	{
		MaxAmmo->SetText(FText::AsNumber(MaxAmmoValue));
	}
}

void UTPSHUDWidget::UpdateSpAttack(float CurrentCoolTime, float MaxCoolTime)
{
	if (SpAttackProgressBar)
	{
		SpAttackProgressBar->SetPercent(CurrentCoolTime / MaxCoolTime);
	}
}

void UTPSHUDWidget::UpdateDrone(float CurrentCoolTime, float MaxCoolTime)
{
	if (DroneProgressBar)
	{
		DroneProgressBar->SetPercent(CurrentCoolTime / MaxCoolTime);
	}
}

void UTPSHUDWidget::UpdateUltimate(int32 CurrentGauge, int32 MaxGauge)
{
	int32 ProgressRatio = float(CurrentGauge) / float(MaxGauge) * 100.0f;

	if (UltimateProgressValue)
	{
		UltimateProgressValue->SetText(FText::AsNumber(ProgressRatio));
	}

	if (UltimateProgress)
	{
		UMaterialInstanceDynamic* CircularProgress = UltimateProgress->GetDynamicMaterial();
		if (CircularProgress)
		{
			CircularProgress->SetScalarParameterValue("CircularProgress01_Blue", float(CurrentGauge) / float(MaxGauge));
		}

	}
}

void UTPSHUDWidget::UpdateTargetHP(int32 CurrentHPValue, int32 MaxHPValue)
{
	if (TargetHPBar)
	{
		float HPPercent = float(CurrentHPValue) / float(MaxHPValue);

		TargetHPBar->SetPercent(HPPercent);

		// HPBar 보이기
		TargetHPBar->SetVisibility(ESlateVisibility::Visible);

		// 이전 타이머 클리어
		GetWorld()->GetTimerManager().ClearTimer(HPBarHideTimerHandle);

		// 5초 후에 숨기도록 타이머 시작
		GetWorld()->GetTimerManager().SetTimer(
			HPBarHideTimerHandle,
			this,
			&UTPSHUDWidget::HideTargetHPBar,
			5.0f,
			false
		);
	}
}

void UTPSHUDWidget::UpdateTargetName(FText NewName)
{
	if (TargetName)
	{
		TargetName->SetText(NewName);

		TargetName->SetVisibility(ESlateVisibility::Visible);

		// 이전 타이머 클리어
		GetWorld()->GetTimerManager().ClearTimer(NameHideTimerHandle);

		// 5초 후에 숨기도록 타이머 시작
		GetWorld()->GetTimerManager().SetTimer(
			NameHideTimerHandle,
			this,
			&UTPSHUDWidget::HideTargetName,
			5.0f,
			false
		);
	}
}

void UTPSHUDWidget::HideTargetHPBar()
{
	if (TargetHPBar)
	{
		TargetHPBar->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTPSHUDWidget::HideTargetName()
{
	if (TargetName)
	{
		TargetName->SetVisibility(ESlateVisibility::Hidden);
	}
}
