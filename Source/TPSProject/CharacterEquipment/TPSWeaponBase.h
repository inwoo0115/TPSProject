// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "TPSWeaponBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	// 특성 배열에 추가
	virtual void AddAbility(UTPSEquipmentAbilityBase* NewAbility);

	// 특성 배열 초기화
	virtual void ClearAbilitySlot();

	// 컴포넌트에 특성 적용
	virtual void InitializeAbilities();

	// 무기 장착 시 오너 컴포넌트 등록
	virtual void InitializeComponent(UActorComponent* InitializeComponent);

	UPROPERTY()
	TObjectPtr<class UTPSEquipmentAbilityData> AbilityData;

	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

protected:
	UPROPERTY()
	TObjectPtr<class UActorComponent> OwnerComponent;
};
