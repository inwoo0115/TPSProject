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

	// Replication ¼¼ÆÃ
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CaculateDamage(float TakeDamage);

	void UpdateHp(float HpDelta);

protected:

	// Ä³¸¯ÅÍ ½ºÅÈ
	UPROPERTY(ReplicatedUsing=OnRep_CurrentHP, Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHP;
	
	UPROPERTY(Replicated, Transient, VisibleInstanceOnly, Category = Stat)
	float MaxHP;

	UPROPERTY(Replicated, Transient, VisibleInstanceOnly, Category = Stat)
	float Defensive;

	UPROPERTY(Replicated, Transient, VisibleInstanceOnly, Category = Stat)
	float Damage;

	// ÀÌº¥Æ® ½Ì±ÛÅæ Ä³½Ì
	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSubsystem> EventSystem;

	// OnRep ÄÝ¹é
	UFUNCTION()
	void OnRep_CurrentHP();
};
