// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSUltimateActorBase.h"

// Sets default values
ATPSUltimateActorBase::ATPSUltimateActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPSUltimateActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSUltimateActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

