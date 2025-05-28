// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPSLobbyGameMode.h"
#include "Character/TPSCharacterPlayer.h"
#include "Character/TPSCharacterControlData.h"

ATPSLobbyGameMode::ATPSLobbyGameMode()
{
	// Default Pawn Class ����
	static ConstructorHelpers::FClassFinder<APawn> DefaultCharacterRef(TEXT("/Script/TPSProject.TPSCharacterPlayer"));
	if (DefaultCharacterRef.Class)
	{
		DefaultPawnClass = DefaultCharacterRef.Class;
	}

	// Default Controller Class ����
	static ConstructorHelpers::FClassFinder<APlayerController> DefaultControllerRef(TEXT("/Script/TPSProject.TPSPlayerController"));
	if (DefaultControllerRef.Class)
	{
		PlayerControllerClass = DefaultControllerRef.Class;
	}
}

void ATPSLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Pawn�� Ȯ�������� �������� ���� �ٽ� ����
	RestartPlayer(NewPlayer);

	// Character Control Setting
	if (ATPSCharacterPlayer* PlayerCharacter = Cast<ATPSCharacterPlayer>(NewPlayer->GetPawn()))
	{
		PlayerCharacter->SetCharacterControlData(ECharacterControlType::NonCombat);
	}
}
