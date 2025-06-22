// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSSpAttackSettingWidget.h"
#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "GameInstance/TPSGameInstance.h"

void UTPSSpAttackSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfrimButton)
		ConfrimButton->OnClicked.AddDynamic(this, &UTPSSpAttackSettingWidget::OnConfirmButtonClicked);


	// ¿ß¡¨ √ ±‚»≠
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn && Pawn->SpAttackComponent->Equipment)
	{
		const ATPSSpAttackSkillBase* Equipment = Cast<ATPSSpAttackSkillBase>(Pawn->SpAttackComponent->Equipment);
		if (Equipment)
		{
			InitializeWidget(Pawn->SpAttackComponent->Equipment, Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
		}
	}
}

void UTPSSpAttackSettingWidget::EquipBySelectWidget(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn)
	{
		auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
		if (TPSGameInstance)
		{
			Pawn->SpAttackComponent->Equip(
				TPSGameInstance->SpAttackSkillEquipmentClass,
				Ability1,
				Ability2,
				Ability3
			);
		}
	}
}
