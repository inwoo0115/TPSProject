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

	// 컴포넌트에 특성 적용
	virtual void InitializeAbilities();

	// 무기 의존성 주입
	void InitializeComponent(UActorComponent* InitComponent);

	// 데이터 에셋에서 특성 초기화
	void InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// 특성 델리게이트 해제
	void ClearAbilityDelegates();

	// 사용가능한 전체 특성 배열
	UPROPERTY(ReplicatedUsing = OnRep_AbilitySlot)
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

	// 델리게이트 해제 용 캐싱 슬롯
	UPROPERTY()
	TArray<class UTPSEquipmentAbilityBase*> PreviousSlot;

	// 특성 배열 변화 시 적용
	UFUNCTION()
	void OnRep_AbilitySlot();

	// 특성 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TSubclassOf<class UTPSEquipmentAbilityBase>> AbilityList;

	UFUNCTION(BlueprintCallable)
	UActorComponent* GetOwnerComponent() const;
	

protected:
	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 오너 컴포넌트
	UPROPERTY(Replicated)
	TObjectPtr<class UActorComponent> OwnerComponent;

	// 수동 리플리케이션
	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSubsystem> EventSystem;
};
