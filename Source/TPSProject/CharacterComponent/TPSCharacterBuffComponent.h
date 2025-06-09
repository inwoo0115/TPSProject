// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSCharacterBuffComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSPROJECT_API UTPSCharacterBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTPSCharacterBuffComponent();

	// �̺�Ʈ �ý��� ���
	void Initialize(UTPSGameplayEventSystem* InputEventSystem);

protected:
	void GetBuffByField(FName FieldName, float& OutDamage);

	UPROPERTY()
	TObjectPtr<class UTPSGameplayEventSystem> EventSystem;
		
};
