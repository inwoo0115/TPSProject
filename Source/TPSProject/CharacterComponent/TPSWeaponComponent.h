// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterEquipment/TPSWeaponBase.h"
#include "TPSWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTPSWeaponComponent();

	void BeginPlay() override;
	
	void EquipWeapon(TSubclassOf<ATPSWeaponBase> WeaponClass);

	void Fire();
	
	void Aim();

	void Reload();

protected:

	UPROPERTY()
	TObjectPtr<class ATPSWeaponBase> EquippedWeapon;

	UPROPERTY()
	TObjectPtr<class UTPSWeaponData> EquippedWeaponData;

	int32 CurrentAmmo;
};
