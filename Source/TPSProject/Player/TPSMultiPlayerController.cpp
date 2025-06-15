// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSMultiPlayerController.h"
#include "Character/TPSCharacterBase.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "Widget/TPSHUDWidget.h"


ATPSMultiPlayerController::ATPSMultiPlayerController()
{
	static ConstructorHelpers::FClassFinder<UTPSHUDWidget> HUDWidgetRef(TEXT("/Game/TPSProject/Widget/WB_HUD.WB_HUD_C"));
	if (HUDWidgetRef.Class)
	{
		HUDWidgetClass = HUDWidgetRef.Class;
	}
}

void ATPSMultiPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn)
	{
		return;
	}

	ATPSCharacterBase* PlayerCharacter = Cast<ATPSCharacterBase>(InPawn);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetCharacterControlData(ECharacterControlType::Combat);
	}
}

void ATPSMultiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		UTPSHUDWidget* HUD = CreateWidget<UTPSHUDWidget>(this, HUDWidgetClass);
		if (HUD)
		{
			HUD->AddToViewport(5);
			HUD->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
