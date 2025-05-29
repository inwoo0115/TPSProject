// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSOnlineSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

void UTPSOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// 현재 플랫폼에 대한 Online subsystem interface를 가져옴
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// Interface 함수에 대한 콜백 함수 추가
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

	// Lan mode로 생성
	SessionSettings->bIsLANMatch = true;

	// 세션 접속 수
	SessionSettings->NumPublicConnections = 4;

	// 세션 탐색 시 발견 가능
	SessionSettings->bShouldAdvertise = true;
	SessionSettings->bUsesPresence = true;

	// 세션 커스텀 데이터 추가 : 세션 이름
	SessionSettings->Set(FName("SERVER_NAME_KEY"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	// 세션 생성
	SessionInterface->CreateSession(0, NAME_GameSession, *SessionSettings);
}

void UTPSOnlineSubsystem::FindSession()
{
	if (!SessionInterface.IsValid()) return;

	SessionSearch = MakeShared<FOnlineSessionSearch>();

	// Lan Session만 검색
	SessionSearch->bIsLanQuery = true;

	// 검색 수
	SessionSearch->MaxSearchResults = 100;

	// 세션 검색 필터
	SessionSearch->QuerySettings.Set(FName(TEXT("Presence")), true, EOnlineComparisonOp::Equals);


	// 세션 찾기
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
		// 멀티플레이 레벨 전환
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session."));
	}
}

void UTPSOnlineSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	// SessionSearch->SearchResults로 세션 결과 저장
}

void UTPSOnlineSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}
