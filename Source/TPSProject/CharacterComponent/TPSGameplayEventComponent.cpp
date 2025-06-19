// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSGameplayEventComponent.h"


UTPSGameplayEventComponent::UTPSGameplayEventComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

}


