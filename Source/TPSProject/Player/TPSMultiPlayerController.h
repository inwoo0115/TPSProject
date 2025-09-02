// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/TPSPlayerController.h"
#include "Interface/TPSSetTargetInterface.h"
#include "TPSMultiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSMultiPlayerController : public ATPSPlayerController, public ITPSSetTargetInterface
{
	GENERATED_BODY()

public:
	ATPSMultiPlayerController();

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void SetTarget(AActor* NewTarget) override;

	UPROPERTY()
	TObjectPtr<AActor> CurrentTarget;

	UFUNCTION(Client, Reliable)
	void ClientUpdateTarget(AActor* Target);  // 클라이언트 RPC

	UFUNCTION(Server, Reliable)
	void ServerInitializeAbilityList(
		const TArray<EAbilityType>& WeaponKeys,
		const TArray<TSubclassOf<class UTPSEquipmentAbilityBase>>& WeaponValues,
		const TArray<EAbilityType>& DroneKeys,
		const TArray<TSubclassOf<class UTPSEquipmentAbilityBase>>& DroneValues,
		const TArray<EAbilityType>& SpAttackKeys,
		const TArray<TSubclassOf<class UTPSEquipmentAbilityBase>>& SpAttackValues,
		const TArray<EAbilityType>& UltimateKeys,
		const TArray<TSubclassOf<class UTPSEquipmentAbilityBase>>& UltimateValues);

	void SerializeDataFromList(
		TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>>& List,
		TArray<EAbilityType>& OutKeys,
		TArray<TSubclassOf<class UTPSEquipmentAbilityBase>>& OutValues);

	// 개인 장착 특성 모음
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> WeaponAbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> DroneAbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> SpAttackAbilityList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TObjectPtr<class UTPSAbilityItem>> UltimateAbilityList;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UTPSHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UTPSHUDWidget> HUDWidget;
};
