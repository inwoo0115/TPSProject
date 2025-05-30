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
    // 싱글 플레이 레벨 전환
    UGameplayStatics::OpenLevel(this, FName("DemoLevel"));

    // 위젯 상태 초기화
    GetGameInstance()->GetSubsystem<UTPSUiSubsystem>()->HideCurrentUI();
}
