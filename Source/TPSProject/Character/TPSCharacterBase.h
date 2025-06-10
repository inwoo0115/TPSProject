// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	NonCombat,
	Combat
};

UCLASS()
class TPSPROJECT_API ATPSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacterBase();

	virtual void BeginPlay() override;

	void SetCharacterControlData(ECharacterControlType ControlType);

	// AnimMontage 데이터 에셋
	UPROPERTY(EditAnywhere, Category = AnimMontage)
	TObjectPtr<class UTPSAnimMontageData> AnimMontageData;

	// Getter
	FVector GetCameraLocation() const;

	FRotator GetCameraRotation() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<class UTPSWeaponComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<class UTPSCharacterStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone")
	TObjectPtr<class UTPSDroneSkillComponent> DroneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpAttack")
	TObjectPtr<class UTPSSpAttackSkillComponent> SpAttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate")
	TObjectPtr<class UTPSUltimateComponent> UltimateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EventSystem")
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;

protected:

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UTPSCharacterControlData*> CharacterControlManager;

	UPROPERTY(ReplicatedUsing = OnRep_ControlType)
	ECharacterControlType CurrentCharacterControlType = ECharacterControlType::Combat;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_ControlType();

	// 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cable")
	TObjectPtr<class UTPSRopeActionComponent> RopeActionComponent;


};
