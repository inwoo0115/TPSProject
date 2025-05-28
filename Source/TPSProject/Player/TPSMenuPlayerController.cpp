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

	// 컨트롤러 생성 후 UI widget 등록
	auto UiSubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UiSubsystem)
	{
		UiSubsystem->RefreshWidgetsForNewController(this);

	// 메인 화면 출력
		UiSubsystem->ShowUI(EUIType::Main);
	}
}
