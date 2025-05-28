// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSMenuPlayerController.h"
#include "GameInstance/TPSUiSubsystem.h"

void ATPSMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	bShowMouseCursor = true;

	// ��Ʈ�ѷ� ���� �� UI widget ���
	auto UiSubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UiSubsystem)
	{
		UiSubsystem->RefreshWidgetsForNewController(this);

	// ���� ȭ�� ���
		UiSubsystem->ShowUI(EUIType::Main);
	}
}
