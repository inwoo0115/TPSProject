// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSWeaponAbilitySelectWidget.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "GameInstance/TPSGameInstance.h"

void UTPSWeaponAbilitySelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfrimButton01) ConfrimButton01->OnClicked.AddDynamic(this, &UTPSWeaponAbilitySelectWidget::OnEquipment01ConfrimClicked);
	if (ConfrimButton02) ConfrimButton02->OnClicked.AddDynamic(this, &UTPSWeaponAbilitySelectWidget::OnEquipment02ConfrimClicked);

}

void UTPSWeaponAbilitySelectWidget::OnEquipment01ConfrimClicked()
{
	// 무기 장착
	EAbilityType Ability1 = EAbilityType::None;
	EAbilityType Ability2 = EAbilityType::None;
	EAbilityType Ability3 = EAbilityType::None;


	// TODO : Weapon임시 장착 (나중에 게임 인스턴스에서 한번에 불러올것)
	auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
	if (TPSGameInstance)
	{
		// 무기 장착
		ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
		if (Pawn)
		{
			if (RowSelectedButtons.Contains(1))
			{
				Ability1 = ButtonToAbilityMap[RowSelectedButtons[1]];		
			}
			if (RowSelectedButtons.Contains(2))
			{
				Ability2 = ButtonToAbilityMap[RowSelectedButtons[2]];		
			}
			if (RowSelectedButtons.Contains(3))
			{
				Ability3 = ButtonToAbilityMap[RowSelectedButtons[3]];		
			}

			Pawn->WeaponComponent->EquipWeapon(
				TPSGameInstance->WeaponClass,
				Ability1,
				Ability2,
				Ability3
			);
		}
	}
	ResetToggleButton();
}

void UTPSWeaponAbilitySelectWidget::OnEquipment02ConfrimClicked()
{
	EAbilityType Ability1 = EAbilityType::None;
	EAbilityType Ability2 = EAbilityType::None;
	EAbilityType Ability3 = EAbilityType::None;


	// TODO : Weapon임시 장착 (나중에 게임 인스턴스에서 한번에 불러올것)
	auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
	if (TPSGameInstance)
	{
		// 무기 장착
		ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
		if (Pawn)
		{
			if (RowSelectedButtons.Contains(1))
			{
				Ability1 = ButtonToAbilityMap[RowSelectedButtons[1]];
			}
			if (RowSelectedButtons.Contains(2))
			{
				Ability2 = ButtonToAbilityMap[RowSelectedButtons[2]];
			}
			if (RowSelectedButtons.Contains(3))
			{
				Ability3 = ButtonToAbilityMap[RowSelectedButtons[3]];
			}

			Pawn->WeaponComponent->EquipWeapon(
				TPSGameInstance->WeaponClass,
				Ability1,
				Ability2,
				Ability3
				);
		}
	}
	ResetToggleButton();
}
