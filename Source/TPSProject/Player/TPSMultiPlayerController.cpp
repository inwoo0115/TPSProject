// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSMultiPlayerController.h"
#include "Character/TPSCharacterBase.h"

void ATPSMultiPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed Pawn: "));

		return;
	}

	ATPSCharacterBase* PlayerCharacter = Cast<ATPSCharacterBase>(InPawn);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetCharacterControlData(ECharacterControlType::Combat);
	}
}
