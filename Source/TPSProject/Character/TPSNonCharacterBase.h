// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSNonCharacterBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSNonCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATPSNonCharacterBase();

	UPROPERTY(EditAnywhere)
	FText CharacterName;

	UPROPERTY(Replicated, EditAnywhere)
	float CurrentHp = 1000.0f;

	UPROPERTY(Replicated, EditAnywhere)
	float MaxHp = 1000.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	float CalculateDamage(float Damage);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
