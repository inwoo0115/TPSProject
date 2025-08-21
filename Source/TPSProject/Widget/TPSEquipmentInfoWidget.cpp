// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSEquipmentInfoWidget.h"
#include "TPSEquipmentInfoWidget.h"
#include "Character/TPSCharacterBase.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterComponent/TPSDroneSkillComponent.h"
#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "CharacterComponent/TPSUltimateComponent.h"
#include "CharacterEquipment/TPSDroneSkillBase.h"
#include "CharacterEquipment/TPSUltimateSkillBase.h"
#include "CharacterEquipment/TPSSpAttackSkillBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UTPSEquipmentInfoWidget::InitializeWeaponInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	FWeaponContext Context = Pawn->WeaponComponent->GetWeapon()->GetWeaponContext();

	SetImageAndText(Context.WeaponIcon, Context.WeaponName);
	SetAbilities(Pawn->WeaponComponent->GetWeapon()->AbilityList);
}

void UTPSEquipmentInfoWidget::InitializeDroneInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSDroneSkillBase* Equipment = Cast<ATPSDroneSkillBase>(Pawn->DroneComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	SetAbilities(Equipment->AbilityList);
}

void UTPSEquipmentInfoWidget::InitializeUltimateInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSUltimateSkillBase* Equipment = Cast<ATPSUltimateSkillBase>(Pawn->UltimateComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	SetAbilities(Equipment->AbilityList);
}

void UTPSEquipmentInfoWidget::InitializeSpAttackInfo()
{
	ATPSCharacterBase* Pawn = Cast<ATPSCharacterBase>(GetOwningPlayerPawn());

	const ATPSSpAttackSkillBase* Equipment = Cast<ATPSSpAttackSkillBase>(Pawn->SpAttackComponent->GetEquipment());

	SetImageAndText(Equipment->GetSkillContext().SkillEquipmentIcon, Equipment->GetSkillContext().SkillEquipmentName);
	SetAbilities(Equipment->AbilityList);
}

void UTPSEquipmentInfoWidget::SetImageAndText(TSoftObjectPtr<UTexture2D> Icon, FText ContextName)
{
	// 이미지 장비 텍스쳐 할당
	Icon.LoadSynchronous();
	UTexture2D* IconTexture = Icon.Get();
	if (IconTexture)
		EquipmentIcon->SetBrushFromTexture(IconTexture);

	// 장비 이름 할당
	EquipmentName->SetText(ContextName);
}

void UTPSEquipmentInfoWidget::SetAbilities(TMap<EAbilityType, TSubclassOf<class UTPSEquipmentAbilityBase>> List)
{
	if (List.Find(EAbilityType::Group1Ability1))
	{
		
	}

	if (List.Find(EAbilityType::Group1Ability2))
	{

	}

	if (List.Find(EAbilityType::Group2Ability1))
	{

	}

	if (List.Find(EAbilityType::Group2Ability2))
	{

	}

	if (List.Find(EAbilityType::Group3Ability1))
	{

	}

	if (List.Find(EAbilityType::Group3Ability2))
	{

	}
}


void UTPSEquipmentInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
