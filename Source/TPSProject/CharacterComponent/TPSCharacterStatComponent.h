// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSCharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSCharacterStatComponent();

	virtual void BeginPlay() override;

protected:
	void GetDamageByField(FName FieldName, float &OutDamage);

	// Ä³¸¯ÅÍ ½ºÅÈ
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float Defensive;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float Damage;

	// ÀÌº¥Æ® ½Ì±ÛÅæ Ä³½Ì
	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSubsystem> EventSystem;
};
