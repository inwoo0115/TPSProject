// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSOnlineSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"

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
	SessionSearch->MaxSearchResults = 20;

	// 세션 검색 필터
	SessionSearch->QuerySettings.Set(FName(TEXT("Presence")), true, EOnlineComparisonOp::Equals);


	// 세션 찾기
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UTPSOnlineSubsystem::JoinSession(int32 SessionIndex)
{
	if (!SessionInterface.IsValid() || !SessionSearch.IsValid()) return;

	if (SessionIndex < SessionSearch->SearchResults.Num())
	{
		// session index에 해당 하는 세션 참여
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
		// 멀티 플레이 맵 리슨 서버 모드로 호출
		UGameplayStatics::OpenLevel(GetWorld(), "DemoMultiLevel", true, "listen");
	}
}

void UTPSOnlineSubsystem::OnFindSessionsComplete(bool bWasSuccessful)
{
	if (!bWasSuccessful || !SessionSearch.IsValid()) return;


	// SessionSearch->SearchResults로 검색된 세션 가져오기
	for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
	{
		FString ServerName;
		SessionSearch->SearchResults[i].Session.SessionSettings.Get(FName("SERVER_NAME_KEY"), ServerName);

		// 디버그 용 로그 DEBUG
		UE_LOG(LogTemp, Log, TEXT("Session %d: %s"), i, *ServerName);
	}

	// 델리게이트로 위젯에 알림
	OnSessionSearchComplete.Broadcast();
}

void UTPSOnlineSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		return ;
	}

	// IP 주소/포트를 담을 문자열
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
