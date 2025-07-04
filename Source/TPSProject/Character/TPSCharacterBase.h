// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/TPSEventComponentInterface.h"
#include "TPSCharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	NonCombat,
	Combat
};

UCLASS()
class TPSPROJECT_API ATPSCharacterBase : public ACharacter, public ITPSEventComponentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacterBase();

	virtual void BeginPlay() override;

	void SetCharacterControlData(ECharacterControlType ControlType);

	// AnimMontage ������ ����
	UPROPERTY(EditAnywhere, Category = AnimMontage)
	TObjectPtr<class UTPSAnimMontageData> AnimMontageData;

	// �ִ� ��Ÿ�� �켱�� ��
	bool CanPlayMontageByPriority(UAnimMontage* NewPlayMontage);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Event")
	TObjectPtr<class UTPSGameplayEventComponent> EventComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ultimate")
	TObjectPtr<class UTPSUltimateComponent> UltimateComponent;

	virtual UTPSGameplayEventComponent* GetEventComponent() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, \
		AActor* DamageCauser) override;

protected:
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UTPSCharacterControlData*> CharacterControlManager;

	UPROPERTY(ReplicatedUsing = OnRep_ControlType)
	ECharacterControlType CurrentCharacterControlType = ECharacterControlType::Combat;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_ControlType();

	// ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cable")
	TObjectPtr<class UTPSRopeActionComponent> RopeActionComponent;

};
