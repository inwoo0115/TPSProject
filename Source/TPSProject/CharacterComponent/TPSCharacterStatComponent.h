// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSGameplayEventSystem.h"
#include "TPSCharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSCharacterStatComponent();

	// 이벤트 시스템 등록
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);

protected:
	void GetDamageByField(FName FieldName, float &OutDamage);

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

	// 캐릭터 스탯
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float Damage;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float Defense;
};
