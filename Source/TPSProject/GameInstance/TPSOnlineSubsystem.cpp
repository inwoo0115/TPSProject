// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSOnlineSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

void UTPSOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// ���� �÷����� ���� Online subsystem interface�� ������
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// Interface �Լ��� ���� �ݹ� �Լ� �߰�
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UTPSOnlineSubsystem::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UTPSOnlineSubsystem::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UTPSOnlineSubsystem::OnJoinSessionComplete);
		}
	}
}

void UTPSOnlineSubsystem::CreateSession(FString ServerName)
{
	if (!SessionInterface.IsValid()) return;

	SessionSettings = MakeShared<FOnlineSessionSettings>();

	// Lan mode�� ����
	SessionSettings->bIsLANMatch = true;

	// ���� ���� ��
	SessionSettings->NumPublicConnections = 4;

	// ���� Ž�� �� �߰� ����
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;

	// ���� Ŀ���� ������ �߰� : ���� �̸�
	SessionSettings->Set(FName("SERVER_NAME_KEY"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	// ���� ����
	SessionInterface->CreateSession(0, NAME_GameSession, *SessionSettings);
}

void UTPSOnlineSubsystem::FindSession()
{
	if (!SessionInterface.IsValid()) return;

	SessionSearch = MakeShared<FOnlineSessionSearch>();

	// Lan Session�� �˻�
	SessionSearch->bIsLanQuery = true;

	// �˻� ��
	SessionSearch->MaxSearchResults = 20;

	// ���� �˻� ����
	SessionSearch->QuerySettings.Set(FName(TEXT("Presence")), true, EOnlineComparisonOp::Equals);


	// ���� ã��
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UTPSOnlineSubsystem::JoinSession(int32 SessionIndex)
{
	if (!SessionInterface.IsValid() || !SessionSearch.IsValid()) return;

	if (SessionIndex < SessionSearch->SearchResults.Num())
	{
		// session index�� �ش� �ϴ� ���� ����
		SessionInterface->JoinSession(0, NAME_GameSession, SessionSearch->SearchResults[SessionIndex]);
	}
}

const TArray<FOnlineSessionSearchResult>& UTPSOnlineSubsystem::GetSearchResults() const
{
	return SessionSearch->SearchResults;
}

void UTPSOnlineSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// ��Ƽ �÷��� �� ���� ���� ���� ȣ��
		UGameplayStatics::OpenLevel(GetWorld(), "DemoMultiLevel", true, "listen");
	}
}

void UTPSOnlineSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (!bWasSuccessful || !SessionSearch.IsValid()) return;


	// SessionSearch->SearchResults�� �˻��� ���� ��������
	for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
	{
		FString ServerName;
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(FName("SERVER_NAME_KEY"), ServerName);

		// ����� �� �α� DEBUG
		UE_LOG(LogTemp, Log, TEXT("Session %d: %s"), i, *ServerName);
	}

	// ��������Ʈ�� ������ �˸�
	OnSessionSearchComplete.Broadcast();
}

void UTPSOnlineSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		return ;
	}

	// IP �ּ�/��Ʈ�� ���� ���ڿ�
	FString ConnectString;

	if (SessionInterface->GetResolvedConnectString(SessionName, ConnectString))
	{
		APlayerController* PC = GetGameInstance()->GetFirstLocalPlayerController();
		if (PC)
		{
			PC->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
		}
	}
}
