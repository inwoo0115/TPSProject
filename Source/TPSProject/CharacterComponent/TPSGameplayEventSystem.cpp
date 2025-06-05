// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSGameplayEventSystem.h"

void UTPSGameplayEventSystem::BroadCastOnStatChanged(FName FieldName, float NewStat)
{
	OnStatChanged.Broadcast(FieldName, NewStat);
}
