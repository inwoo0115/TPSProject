// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/TPSUiSubsystem.h"


void UTPSMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (Btn_MainMenu1)
    {
        Btn_MainMenu1->OnClicked.AddDynamic(this, &UTPSMenuWidget::OnStartButtonClicked);
        Btn_MainMenu4->OnClicked.AddDynamic(this, &UTPSMenuWidget::OnQuitButtonClicked);
    }
}

void UTPSMenuWidget::OnStartButtonClicked()
{
    // ���� ���� �ʱ�ȭ
    GetGameInstance()->GetSubsystem<UTPSUiSubsystem>()->HideCurrentUI();
    // �̱� �÷��� ���� ��ȯ
    UGameplayStatics::OpenLevel(this, FName("DemoLevel"));
}

void UTPSMenuWidget::OnQuitButtonClicked()
{
    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->ConsoleCommand("quit");
    }
}
