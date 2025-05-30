// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSCharacterBase.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "TPSCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSCharacterPlayer : public ATPSCharacterBase
{
	GENERATED_BODY()
	
public:
	ATPSCharacterPlayer();

	virtual void BeginPlay() override;
 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetIsAim() const { return IsAim; };

	virtual void Tick(float DeltaSecounds);
protected:
	// SpInteraction UI
	void CheckSpInteractionUI();

	// �Է� �׼�
	void Move(const FInputActionValue& Value);

	void MoveComplete(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump();

	void Run(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void AimIn(const FInputActionValue& Value);

	void AimOut(const FInputActionValue& Value);

	void SpAction(const FInputActionValue& Value);

	void SpAttack(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void Drone(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	void Ultimate(const FInputActionValue& Value);

	void Esc(const FInputActionValue& Value);

	void Info(const FInputActionValue& Value);

	// �Է� ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SpActionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> SpAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> EscAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InfoAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> UltimateAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DroneAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InteractAction;

	//���� ���ý�Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InputContext, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	// �÷���
	bool IsRun = false;

	bool IsAttack = false;

	bool IsJump = true;

	bool IsThrow = true;

	bool IsAim = false;


	// Spinteraction Ÿ�� ����
	TObjectPtr<class ATPSSpInteractionObjectBase> SpInteractionTargetActor;
};
