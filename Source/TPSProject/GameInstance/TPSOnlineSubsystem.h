// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Templates/SharedPointer.h"
#include "TPSOnlineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSOnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void CreateSession(FString ServerName);

	void FindSession();

	void JoinSession();

	//void StartSession();
	
	//void DestroySession();

protected:

	// Callback for member delegate
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	//void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	//void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	// 세션 찾기용 조건 객체
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// 세션 생성용 설정
	TSharedPtr<FOnlineSessionSettings> SessionSettings;

	// 세션 인터페이스
	IOnlineSessionPtr SessionInterface;

};
