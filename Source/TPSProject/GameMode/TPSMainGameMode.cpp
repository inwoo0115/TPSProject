// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSMainGameMode.h"
#include "Character/TPSCharacterPlayer.h"
#include "Character/TPSCharacterControlData.h"

ATPSMainGameMode::ATPSMainGameMode()
{
	// Default Pawn Class 설정
	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacterRef(TEXT("/Script/TPSProject.TPSCharacterPlayer"));
	if (DefaultCharacterRef.Class)
	{
		DefaultPawnClass = DefaultCharacterRef.Class;
	}

	// Default Controller Class 설정
	static ConstructorHelpers::FClassFinder<APlayerController> DefaultControllerRef(TEXT("/Script/TPSProject.TPSMultiPlayerController"));
	if (DefaultControllerRef.Class)
	{
		PlayerControllerClass = DefaultControllerRef.Class;
	}
}

void ATPSMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
