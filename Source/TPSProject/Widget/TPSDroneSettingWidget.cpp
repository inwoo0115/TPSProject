// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSDroneSettingWidget.h"
#include "CharacterComponent/TPSDroneSkillComponent.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "GameInstance/TPSGameInstance.h"

void UTPSDroneSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ConfrimButton)
		ConfrimButton->OnClicked.AddDynamic(this, &UTPSDroneSettingWidget::OnConfirmButtonClicked);


	// ¿ß¡¨ √ ±‚»≠
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn && Pawn->DroneComponent->Equipment)
	{
		const ATPSDroneSkillBase* Equipment = Cast<ATPSDroneSkillBase>(Pawn->DroneComponent->Equipment);
		if (Equipment)
		{
			InitializeWidget(Pawn->DroneComponent->Equipment, Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
		}
	}
}

void UTPSDroneSettingWidget::EquipBySelectWidget(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());
	if (Pawn)
	{
		auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
		if (TPSGameInstance)
		{
			Pawn->DroneComponent->Equip(
				TPSGameInstance->DroneSkillEquipmentClass,
				Ability1,
				Ability2,
				Ability3
			);
		}
	}
}
