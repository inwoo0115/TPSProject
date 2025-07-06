// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSMainGameMode.h"
#include "Character/TPSCharacterPlayer.h"
#include "Character/TPSCharacterControlData.h"
#include "PoolManager/TPSPoolManager.h"

ATPSMainGameMode::ATPSMainGameMode()
{
	// Default Pawn Class ����
	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacterRef(TEXT("/Script/TPSProject.TPSCharacterPlayer"));
	if (DefaultCharacterRef.Class)
	{
		DefaultPawnClass = DefaultCharacterRef.Class;
	}

	// Default Controller Class ����
	static ConstructorHelpers::FClassFinder<APlayerController> DefaultControllerRef(TEXT("/Script/TPSProject.TPSMultiPlayerController"));
	if (DefaultControllerRef.Class)
	{
		PlayerControllerClass = DefaultControllerRef.Class;
	}
}

void ATPSMainGameMode::StartPlay()
{
	Super::StartPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	// ������Ʈ Ǯ ���� �� ���ø����̼�
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.bNoFail = true;

	ATPSPoolManager* PoolManager = World->SpawnActor<ATPSPoolManager>(ATPSPoolManager::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);
	if (PoolManager)
	{
		PoolManager->SetReplicates(true);
		PoolManager->SetReplicateMovement(false);
	}
}
