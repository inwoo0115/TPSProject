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

 // ���� �˻� �Ϸ� �˸���
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionSearchCompleteDelegate);

UCLASS()
class TPSPROJECT_API UTPSOnlineSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void CreateSession(FString ServerName);

	void FindSession();

	void JoinSession(int32 SessionIndex);

	const TArray<FOnlineSessionSearchResult>& GetSearchResults() const;

	//void StartSession();
	
	//void DestroySession();

	// ���� ã��� ���� ��ü
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// ���� ������ ����
	TSharedPtr<FOnlineSessionSettings> SessionSettings;

	// ���� �������̽�
	IOnlineSessionPtr SessionInterface;

	// ���� �˻� �Ϸ� ��������Ʈ
	FOnSessionSearchCompleteDelegate OnSessionSearchComplete;
protected:

	// Callback for member delegate
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	bool bIsSearching = false;


	//void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	//void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

};
