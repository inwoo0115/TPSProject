// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSUltimateSettingWidget.h"
#include "Widget/TPSUltimateSettingWidget.h"
#include "CharacterComponent/TPSUltimateComponent.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "GameInstance/TPSGameInstance.h"

void UTPSUltimateSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfrimButton)
		ConfrimButton->OnClicked.AddDynamic(this, &UTPSUltimateSettingWidget::OnConfirmButtonClicked);


	// ¿ß¡¨ √ ±‚»≠
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn && Pawn->UltimateComponent->Equipment)
	{
		const ATPSUltimateSkillBase* Equipment = Cast<ATPSUltimateSkillBase>(Pawn->UltimateComponent->Equipment);
		if (Equipment)
		{
			InitializeWidget(Pawn->UltimateComponent->Equipment, Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
		}
	}
}

void UTPSUltimateSettingWidget::EquipBySelectWidget(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn)
	{
		auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
		if (TPSGameInstance)
		{
			Pawn->UltimateComponent->Equip(
				TPSGameInstance->UltimateSkillEquipmentClass,
				Ability1,
				Ability2,
				Ability3
			);
		}
	}
}
