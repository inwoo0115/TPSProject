// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TPSUiSubsystem.generated.h"

UENUM(BlueprintType)
enum class EUIType : uint8
{
	None	UMETA(DisplayName = "None"),
	Main	UMETA(DisplayName = "Main"),
	Loading	UMETA(DisplayName = "Loading"),
	Pause	UMETA(DisplayName = "Pause"),
	Info	UMETA(DisplayName = "Info"),
	Online	UMETA(DisplayName = "Online"),
	Ability UMETA(DisplayName = "Ability")
};

USTRUCT()
struct FUIInfo
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* Widget = nullptr;

	UPROPERTY()
	TSubclassOf<UUserWidget> WidgetClass;
};


/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSUiSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void ShowUI(EUIType Type);

	void HideUI(EUIType Type);

	void HideCurrentUI();

	void RefreshWidgetsForNewController(APlayerController* NewPC);

	EUIType	GetCurrentUI();

protected:
	void LoadWidget(EUIType UIType, const TSoftClassPtr<UUserWidget>& WidgetClass);

	UPROPERTY()
	TMap<EUIType, FUIInfo> UIManager;

	EUIType CurrentUI = EUIType::None;
};
