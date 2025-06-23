// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;

	void UpdateHP(int32 CurrentHPValue, int32 MaxHPValue);

	void UpdateAmmo(int32 CurrentAmmoValue, int32 MaxAmmoValue);

	void UpdateSpAttack(float CurrentCoolTime, float MaxCoolTime);

	void UpdateDrone(float CurrentCoolTime, float MaxCoolTime);

	void UpdateUltimate(int32 CurrentGauge, int32 MaxGauge);

	void UpdateTargetHP(int32 CurrentHPValue, int32 MaxHPValue);

	void UpdateTargetName(FText NewName);

public:
	// HP UI
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHP;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHP;

	// Weapon UI
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentAmmo;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxAmmo;

	// Skill UI
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SpAttackProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* DroneProgressBar;

	// ±Ã±Ø±â UI
	UPROPERTY(meta = (BindWidget))
	class UImage* UltimateProgress;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UltimateProgressValue;

	// Enemy UI
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* TargetHPBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TargetName;

	// Target UI Timer
	FTimerHandle HPBarHideTimerHandle;
	FTimerHandle NameHideTimerHandle;

	void HideTargetHPBar();

	void HideTargetName();
};
