// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSOnlineMenuWidget.h"
#include "TPSOnlineMenuWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/EditableText.h"
#include "Components/CanvasPanel.h"

void UTPSOnlineMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &UTPSOnlineMenuWidget::OnHostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UTPSOnlineMenuWidget::OnJoinButtonClicked);
	}
	ServerListPanel->SetVisibility(ESlateVisibility::Hidden);
	ServerNamePanel->SetVisibility(ESlateVisibility::Hidden);
}

void UTPSOnlineMenuWidget::OnHostButtonClicked()
{
	ServerListPanel->SetVisibility(ESlateVisibility::Hidden);
	ServerNamePanel->SetVisibility(ESlateVisibility::Visible);
}

void UTPSOnlineMenuWidget::OnJoinButtonClicked()
{
	ServerListPanel->SetVisibility(ESlateVisibility::Visible);
	ServerNamePanel->SetVisibility(ESlateVisibility::Hidden);
}
