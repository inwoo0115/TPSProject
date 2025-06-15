// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "TPSAbilityEquipmentBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSAbilityEquipmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATPSAbilityEquipmentBase();

	virtual void BeginPlay() override;

	// ������Ʈ�� Ư�� ����
	virtual void InitializeAbilities();

	// ���� ������ ����
	void InitializeComponent(UActorComponent* InitComponent);

	// ������ ���¿��� Ư�� �ʱ�ȭ
	void InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// Ư�� ��������Ʈ ����
	void ClearAbilityDelegates();

	// ��밡���� ��ü Ư�� �迭
	UPROPERTY(ReplicatedUsing = OnRep_AbilitySlot)
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

	// ��������Ʈ ���� �� ĳ�� ����
	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> PreviousSlot;

	// Ư�� �迭 ��ȭ �� ����
	UFUNCTION()
	void OnRep_AbilitySlot();

	// Ư�� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TSubclassOf<class UTPSEquipmentAbilityBase>> AbilityList;

	UFUNCTION(BlueprintCallable)
	UActorComponent* GetOwnerComponent() const;
	

protected:
	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// ���� ������Ʈ
	UPROPERTY(Replicated)
	TObjectPtr<class UActorComponent> OwnerComponent;

	// ���� ���ø����̼�
	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSubsystem> EventSystem;
};
