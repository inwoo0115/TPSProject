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

	void SetCharacterControlData(ECharacterControlType ControlType);

protected:
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UTPSCharacterControlData*> CharacterControlManager;

	ECharacterControlType CurrentCharacterControlType = ECharacterControlType::Combat;

	// ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;
};
