// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSPauseWidget.h"
#include "TPSPauseWidget.h"
#include "Components/Button.h"
#include "GameInstance/TPSUiSubsystem.h"

void UTPSPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UTPSPauseWidget::OnResumeButtonClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UTPSPauseWidget::OnQuitButtonClicked);
	}
}

void UTPSPauseWidget::OnResumeButtonClicked()
{
	auto UIsubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UIsubsystem)
	{
		UIsubsystem->HideCurrentUI();
	}
}

void UTPSPauseWidget::OnQuitButtonClicked()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->ConsoleCommand("quit");
	}
}
