// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSServerJoinButtonWidget.h"
#include "Components/Button.h"
#include "GameInstance/TPSOnlineSubsystem.h"

void UTPSServerJoinButtonWidget::NativeConstruct()
{
	if (ServerButton)
	{
		ServerButton->OnClicked.AddDynamic(this, &UTPSServerJoinButtonWidget::OnJoinButtonClicked);
	}
}

void UTPSServerJoinButtonWidget::OnJoinButtonClicked()
{
	auto OnlineSubsystem = GetGameInstance()->GetSubsystem<UTPSOnlineSubsystem>();
	if (OnlineSubsystem)
	{
		OnlineSubsystem->JoinSession(SessionIndex);
	}
}
