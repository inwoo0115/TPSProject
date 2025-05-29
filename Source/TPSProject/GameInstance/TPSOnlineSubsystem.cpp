// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSOnlineSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

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
	SessionSearch->MaxSearchResults = 100;

	// ���� �˻� ����
	SessionSearch->QuerySettings.Set(FName(TEXT("Presence")), true, EOnlineComparisonOp::Equals);


	// ���� ã��
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UTPSOnlineSubsystem::JoinSession()
{
	if (!SessionInterface.IsValid()) return;
}

void UTPSOnlineSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		// ��Ƽ�÷��� ���� ��ȯ
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session."));
	}
}

void UTPSOnlineSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	// SessionSearch->SearchResults�� ���� ��� ����
}

void UTPSOnlineSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}
