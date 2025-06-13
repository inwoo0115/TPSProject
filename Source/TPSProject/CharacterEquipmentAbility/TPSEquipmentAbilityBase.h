// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TPSEquipmentAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSEquipmentAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void InitializeWeaponAbility(FWeaponContext& WeaponContext);

	// UObject 리플리케이션을 위해 오버라이드
	FORCEINLINE bool IsSupportedForNetworking() const override { return true; }

	FORCEINLINE bool ReplicateSubobjects(class AActorChannel* Channel, class FOutBunch* Bunch, struct FReplicationFlags* RepFlags) { return false; }

	int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;

	bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;

	UFUNCTION()
	virtual void ApplyAbility();

	FText AbilityName;

	FText AbilityDescription;
};
