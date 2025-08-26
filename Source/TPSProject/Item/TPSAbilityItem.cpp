// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TPSAbilityItem.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"

void UTPSAbilityItem::InitItem(const FName& InName, TSubclassOf<UTPSEquipmentAbilityBase> InClass)
{
	AbilityName = InName;

	AbilityClass = InClass;
}

FText UTPSAbilityItem::GetAbilityNameText() const
{
	if (AbilityClass)
	{
		const UTPSEquipmentAbilityBase* DefaultObj = AbilityClass->GetDefaultObject<UTPSEquipmentAbilityBase>();
		return DefaultObj->AbilityName;
	}
	return FText::GetEmpty();
}

FText UTPSAbilityItem::GetAbilityDescriptionText() const
{
	if (AbilityClass)
	{
		const UTPSEquipmentAbilityBase* DefaultObj = AbilityClass->GetDefaultObject<UTPSEquipmentAbilityBase>();
		return DefaultObj->AbilityDescription;
	}
	return FText::GetEmpty();
}
