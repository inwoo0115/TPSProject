// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSNonCharacterBase.h"

// Sets default values
ATPSNonCharacterBase::ATPSNonCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATPSNonCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSNonCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSNonCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

