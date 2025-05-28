// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPSLobbyGameMode.h"
#include "Character/TPSCharacterPlayer.h"
#include "Character/TPSCharacterControlData.h"

ATPSLobbyGameMode::ATPSLobbyGameMode()
{
	// Default Pawn Class 설정
	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacterRef(TEXT("/Script/TPSProject.TPSCharacterPlayer"));
	if (DefaultCharacterRef.Class)
	{
		DefaultPawnClass = DefaultCharacterRef.Class;
	}

	// Default Controller Class 설정
	static ConstructorHelpers::FClassFinder<APlayerController> DefaultControllerRef(TEXT("/Script/TPSProject.TPSPlayerController"));
	if (DefaultControllerRef.Class)
	{
		PlayerControllerClass = DefaultControllerRef.Class;
	}
}

void ATPSLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Pawn을 확정적으로 가져오기 위해 다시 실행
	RestartPlayer(NewPlayer);

	// Character Control Setting
	if (ATPSCharacterPlayer* PlayerCharacter = Cast<ATPSCharacterPlayer>(NewPlayer->GetPawn()))
	{
		PlayerCharacter->SetCharacterControlData(ECharacterControlType::NonCombat);
	}
}
