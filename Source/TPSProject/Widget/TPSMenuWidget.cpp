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
    }
}

void UTPSMenuWidget::OnStartButtonClicked()
{
    // �̱� �÷��� ���� ��ȯ
    UGameplayStatics::OpenLevel(this, FName("DemoLevel"));

    // ���� ���� �ʱ�ȭ
    GetGameInstance()->GetSubsystem<UTPSUiSubsystem>()->HideCurrentUI();
}
