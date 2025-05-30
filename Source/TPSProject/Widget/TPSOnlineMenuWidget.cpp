// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSOnlineMenuWidget.h"
#include "TPSOnlineMenuWidget.h"
#include "Components/Button.h"
#include "GameInstance/TPSOnlineSubsystem.h"
#include "Components/CanvasPanel.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "TPSServerJoinButtonWidget.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

UTPSOnlineMenuWidget::UTPSOnlineMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{	
	static ConstructorHelpers::FClassFinder<UUserWidget> ButtonRef(TEXT("/Game/TPSProject/Widget/WB_ServerJoinButton.WB_ServerJoinButton_C"));
	{
		if (ButtonRef.Class)
		{
			ServerButtonWidgetClass = ButtonRef.Class;
		}
	}
}

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
	if (CreateServerButton)
	{
		CreateServerButton->OnClicked.AddDynamic(this, &UTPSOnlineMenuWidget::OnCreateServerButtonClicked);
	}
	ServerListPanel->SetVisibility(ESlateVisibility::Hidden);
	ServerNamePanel->SetVisibility(ESlateVisibility::Hidden);
	CreateServerButton->SetVisibility(ESlateVisibility::Hidden);

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UTPSOnlineSubsystem* OnlineSubsystem = GI->GetSubsystem<UTPSOnlineSubsystem>())
		{
			// 델리게이트 바인딩
			OnlineSubsystem->OnSessionSearchComplete.AddDynamic(this, &UTPSOnlineMenuWidget::OnSessionSearchFinished);
		}
	}
}

void UTPSOnlineMenuWidget::OnHostButtonClicked()
{
	// 빈문자열로 초기화
	ServerName->SetText(FText::FromString(""));

	ServerListPanel->SetVisibility(ESlateVisibility::Hidden);
	ServerNamePanel->SetVisibility(ESlateVisibility::Visible);
	CreateServerButton->SetVisibility(ESlateVisibility::Visible);
}

void UTPSOnlineMenuWidget::OnJoinButtonClicked()
{
	ServerListPanel->SetVisibility(ESlateVisibility::Visible);
	ServerNamePanel->SetVisibility(ESlateVisibility::Hidden);
	CreateServerButton->SetVisibility(ESlateVisibility::Hidden);

	auto OnlineSubsystem = GetGameInstance()->GetSubsystem<UTPSOnlineSubsystem>();
	if (OnlineSubsystem)
	{
		// 기존 내용 정리
		ServerList->ClearChildren();
		OnlineSubsystem->FindSession();
	}
}

void UTPSOnlineMenuWidget::OnCreateServerButtonClicked()
{
	FString InputServerName = (ServerName->GetText()).ToString();

	auto OnlineSubsystem = GetGameInstance()->GetSubsystem<UTPSOnlineSubsystem>();
	if (OnlineSubsystem)
	{
		OnlineSubsystem->CreateSession(InputServerName);
	}
}

void UTPSOnlineMenuWidget::OnSessionSearchFinished()
{
	// OnlineSubsystem에서 session List 가져오기
	auto OnlineSubsystem = GetGameInstance()->GetSubsystem<UTPSOnlineSubsystem>();
	if (OnlineSubsystem)
	{
		auto SearchResults = OnlineSubsystem->GetSearchResults();

		for (int32 i = 0; i < SearchResults.Num(); ++i)
		{
			const auto& Result = SearchResults[i];

			auto* NewServerButton = CreateWidget<UTPSServerJoinButtonWidget>(this, ServerButtonWidgetClass);
			if (NewServerButton)
			{
				NewServerButton->SessionIndex = i;

				FString ServerNameValue;

				if (Result.Session.SessionSettings.Get(FName("SERVER_NAME_KEY"), ServerNameValue))
				{
					NewServerButton->ServerNameText->SetText(FText::FromString(ServerNameValue));
				}
				ServerList->AddChild(NewServerButton);
			}
		}
	}
}
