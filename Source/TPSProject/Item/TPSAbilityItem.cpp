// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/TPSAbilityItem.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "Components/Image.h"

UTPSAbilityItem::UTPSAbilityItem()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextureObj(TEXT("/Game/DARK_SCIFI_UI/Textures/ExampleIcons/T_Icon_Bullets.T_Icon_Bullets"));
	if (TextureObj.Succeeded())
	{
		ItemImage = TextureObj.Object;
	}
}

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

EAbilityType UTPSAbilityItem::GetAbilityType() const
{
	if (AbilityClass)
	{
		const UTPSEquipmentAbilityBase* DefaultObj = AbilityClass->GetDefaultObject<UTPSEquipmentAbilityBase>();
		return DefaultObj->AbilityType;
	}
	return EAbilityType::None;
}

UTexture2D* UTPSAbilityItem::GetItemImage()
{
	return ItemImage;
}

