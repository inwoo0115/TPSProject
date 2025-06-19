// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Interface/TPSEventComponentInterface.h"

void UTPSEquipmentAbilityBase::InitializeWeaponAbility(FWeaponContext& WeaponContext)
{
}


int32 UTPSEquipmentAbilityBase::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
	auto* Owner = GetTypedOuter<AActor>();

	return Owner ? Owner->GetFunctionCallspace(Function, Stack) : FunctionCallspace::Local;
}

bool UTPSEquipmentAbilityBase::CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack)
{
	if (AActor* MyOwner = GetTypedOuter<AActor>())
	{
		if (UNetDriver* NetDriver = MyOwner->GetNetDriver())
		{
			NetDriver->ProcessRemoteFunction(MyOwner, Function, Parameters, OutParms, Stack, this);
			return true;
		}
	}
	return false;
}

void UTPSEquipmentAbilityBase::ApplyAbility()
{
}

void UTPSEquipmentAbilityBase::InitializeAbilityEvent()
{
}

void UTPSEquipmentAbilityBase::CancelAbility()
{
}

UTPSGameplayEventComponent* UTPSEquipmentAbilityBase::GetOwnerEventComponent() const
{
	auto OwnerCharacter = Cast<ITPSEventComponentInterface>(GetOuter());
	if (OwnerCharacter)
	{
		return OwnerCharacter->GetEventComponent();
	}

	return nullptr;
}
