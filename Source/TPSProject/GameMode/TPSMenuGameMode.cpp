// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TPSMenuGameMode.h"
#include "GameInstance/TPSUiSubsystem.h"

ATPSMenuGameMode::ATPSMenuGameMode()
{
    // Default Controller Class ¼³Á¤
    static ConstructorHelpers::FClassFinder<APlayerController> DefaultControllerRef(TEXT("/Script/TPSProject.TPSMenuPlayerController"));
    if (DefaultControllerRef.Class)
    {
        PlayerControllerClass = DefaultControllerRef.Class;
    }
}

void ATPSMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    auto* UISubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
    if (UISubsystem)
    {
        UISubsystem->ShowUI(EUIType::Main);
    }
}
