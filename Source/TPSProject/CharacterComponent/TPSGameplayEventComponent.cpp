// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSGameplayEventComponent.h"

UTPSGameplayEventComponent::UTPSGameplayEventComponent()
{
	// 소유자가 Replicated 되어있는지 확인 후 변경
	SetIsReplicatedByDefault(true);
}
