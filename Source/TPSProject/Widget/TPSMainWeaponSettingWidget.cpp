// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSMainWeaponSettingWidget.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "Character/TPSCharacterBase.h"
#include "GameInstance/TPSGameInstance.h"



void UTPSMainWeaponSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfrimButton)
		ConfrimButton->OnClicked.AddDynamic(this, &UTPSMainWeaponSettingWidget::OnConfirmButtonClicked);


	// ¿ß¡¨ √ ±‚»≠
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn && Pawn->WeaponComponent->GetWeapon())
	{
		const ATPSWeaponBase* Equipment = Pawn->WeaponComponent->GetWeapon();
		InitializeWidget(Pawn->WeaponComponent->GetWeapon(), Equipment->GetWeaponContext().WeaponIcon, Equipment->GetWeaponContext().WeaponName);
	}
}

void UTPSMainWeaponSettingWidget::EquipBySelectWidget(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn)
	{
		auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
		if (TPSGameInstance)
		{
			Pawn->WeaponComponent->EquipWeapon(
				TPSGameInstance->WeaponClass,
				Ability1,
				Ability2,
				Ability3
			);
		}
	}
}


