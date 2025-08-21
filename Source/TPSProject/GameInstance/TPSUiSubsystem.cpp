// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/TPSUiSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "Player/TPSPlayerController.h"
#include "EnhancedInputSubsystems.h"

void UTPSUiSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    // ��� ����
    TSoftClassPtr<UUserWidget> SoftClass_Main(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_MainMenu.WB_MainMenu_C")));
    // map �߰�
    LoadWidget(EUIType::Main, SoftClass_Main);

    // ��� ����
    TSoftClassPtr<UUserWidget> SoftClass_Online(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_OnlineMenu.WB_OnlineMenu_C")));
    // map �߰�
    LoadWidget(EUIType::Online, SoftClass_Online);

    // ��� ����
    TSoftClassPtr<UUserWidget> SoftClass_Pause(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_Pause.WB_Pause_C")));
    // map �߰�
    LoadWidget(EUIType::Pause, SoftClass_Pause);

    // ��� ����
    TSoftClassPtr<UUserWidget> SoftClass_Equipment(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_Equipment.WB_Equipment_C")));
    // map �߰�
    LoadWidget(EUIType::Equipment, SoftClass_Equipment);

    // ��� ����
    TSoftClassPtr<UUserWidget> SoftClass_Inventory(FSoftClassPath(TEXT("/Game/TPSProject/Widget/WB_Inventory.WB_Inventory_C")));
    // map �߰�
    LoadWidget(EUIType::Inventory, SoftClass_Inventory);
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
                // �Է� ��� UI�� �����ϵ��� ����
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
                // ������ �� ���콺�� ����Ʈ�� �ٷ� �Էµǰ�
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
