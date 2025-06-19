// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSCharacterBuffComponent.h"

// Sets default values for this component's properties
UTPSCharacterBuffComponent::UTPSCharacterBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTPSCharacterBuffComponent::GetBuffByField(FName FieldName, float& OutDamage)
{
	// 맵에서 현재 버프 수치 계산
}
