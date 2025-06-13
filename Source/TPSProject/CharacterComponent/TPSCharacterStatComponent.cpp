// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSCharacterStatComponent.h"
#include "TPSGameplayEventSystem.h"

// Sets default values for this component's properties
UTPSCharacterStatComponent::UTPSCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHp = 200;
	MaxHp = 200;
	Damage = 100;
	Defense = 100;
}




void UTPSCharacterStatComponent::GetDamageByField(FName FieldName, float& OutDamage)
{
	// FieldName 으로 맵에서 데미지 가져옴
	OutDamage *= Damage;
}
