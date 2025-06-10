// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSUiSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "TPSUiSubsystem.h"
#include "Player/TPSPlayerController.h"
#include "EnhancedInputSubsystems.h"

void UTPSUiSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    // 경로 저장
    TSoftClassPtr<UUserWidget> SoftClass_Main(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_MainMenu.WB_MainMenu_C")));
    // map 추가
    LoadWidget(EUIType::Main, SoftClass_Main);

    // 경로 저장
    TSoftClassPtr<UUserWidget> SoftClass_Online(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_OnlineMenu.WB_OnlineMenu_C")));
    // map 추가
    LoadWidget(EUIType::Online, SoftClass_Online);

    // 경로 저장
    TSoftClassPtr<UUserWidget> SoftClass_Pause(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_Pause.WB_Pause_C")));
    // map 추가
    LoadWidget(EUIType::Pause, SoftClass_Pause);

    // 경로 저장
    TSoftClassPtr<UUserWidget> SoftClass_Ability(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_WeaponAbilitySelect.WB_WeaponAbilitySelect_C")));
    // map 추가
    LoadWidget(EUIType::Ability, SoftClass_Ability);
}

void UTPSUiSubsystem::ShowUI(EUIType Type)
{
    if (FUIInfo* Info = UIManager.Find(Type))
    {
        if (Info->Widget)
        {
            Info->Widget->SetVisibility(ESlateVisibility::Visible);
            auto *PC = Info->Widget->GetOwningPlayer();
            if (PC)
            {
                // 입력 모드 UI에 집중하도록 설정
                FInputModeUIOnly InputMode;
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(InputMode);

                PC->bShowMouseCursor = true;

                CurrentUI = Type;
            }
        }
    }
}

void UTPSUiSubsystem::HideUI(EUIType Type)
{
    if (FUIInfo* Info = UIManager.Find(Type))
    {
        if (Info->Widget)
        {
            Info->Widget->SetVisibility(ESlateVisibility::Hidden);

            auto* PC = Info->Widget->GetOwningPlayer();
            if (PC)
            {
                // 시작할 때 마우스가 뷰포트로 바로 입력되게
                FInputModeGameOnly GameInput;
                PC->SetInputMode(GameInput);

                PC->bShowMouseCursor = false;

                CurrentUI = EUIType::None;
            }
        }
    }
}

void UTPSUiSubsystem::HideCurrentUI()
{
    HideUI(CurrentUI);
}

void UTPSUiSubsystem::RefreshWidgetsForNewController(APlayerController* NewPC)
{
    for (auto& Elem : UIManager)
    {
        if (Elem.Value.WidgetClass)
        {
            UUserWidget* NewWidget = CreateWidget<UUserWidget>(NewPC, Elem.Value.WidgetClass);
            if (NewWidget)
            {
                Elem.Value.Widget = NewWidget;
                NewWidget->AddToViewport(10);
                NewWidget->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}

EUIType UTPSUiSubsystem::GetCurrentUI()
{
    return CurrentUI;
}

void UTPSUiSubsystem::LoadWidget(EUIType UIType, const TSoftClassPtr<UUserWidget>& WidgetClass)
{
    TSubclassOf<UUserWidget> LoadedClass = WidgetClass.LoadSynchronous();

    if (!LoadedClass)
    {
        return;
    }

    FUIInfo Info;
    Info.WidgetClass = LoadedClass;
    UIManager.Add(UIType, Info);
}
