// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TPSPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

ATPSPlayerController::ATPSPlayerController()
{
	// UI Manager Map Setting
	static ConstructorHelpers::FClassFinder<UUserWidget> DefaultWidgetRef(TEXT("/Game/TPSProject/Widget/WB_InteractionButton.WB_InteractionButton_C"));
	if (DefaultWidgetRef.Class)
	{
		InteractionWidgetClasses.Add(EInteractionUIType::Default, DefaultWidgetRef.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SpecialWidgetRef(TEXT("/Game/TPSProject/Widget/WB_SpInteractionButton.WB_SpInteractionButton_C"));
	if (SpecialWidgetRef.Class)
	{
		InteractionWidgetClasses.Add(EInteractionUIType::Special, SpecialWidgetRef.Class);
	}

	InteractionUIManager.Add(EInteractionUIType::Default, FInteractionUIInfo());
	InteractionUIManager.Add(EInteractionUIType::Special, FInteractionUIInfo());
}

void ATPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ������ �� ���콺�� ����Ʈ�� �ٷ� �Էµǰ�
	FInputModeGameOnly GameInput;

	SetInputMode(GameInput);

	// ��Ʈ�ѷ� ���� �� UI widget ���
	auto UiSubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UiSubsystem)
	{
		UiSubsystem->RefreshWidgetsForNewController(this);
	}
}

void ATPSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (auto& Elem : InteractionUIManager)
	{
		FInteractionUIInfo& UIInfo = Elem.Value;

		if (UIInfo.Widget)
		{
			//Target actor�� ������ ��ġ ����
			if (UIInfo.TargetActor)
			{
				FVector WorldLocation = UIInfo.TargetActor->GetActorLocation();
				FVector2D ScreenPosition;

				if (ProjectWorldLocationToScreen(WorldLocation, ScreenPosition))
				{
					// ȭ�� �ػ� ���� ��ġ ���� �ɼ� : true
					UIInfo.Widget->SetPositionInViewport(ScreenPosition, true);
				}
			}
		}
	}
}

void ATPSPlayerController::SetCanInteract(EInteractionUIType UIType, bool NewInteract)
{
	InteractionUIManager.Find(UIType)->bCanInteract = NewInteract;
}

bool ATPSPlayerController::GetCanInteract(EInteractionUIType UIType)
{
	return InteractionUIManager.Find(UIType)->bCanInteract;
}

void ATPSPlayerController::ShowInteractionUI(EInteractionUIType UIType, AActor* TargetActor)
{
	if (!IsLocalController()) return;

	auto CurrentUIInfo = InteractionUIManager.Find(UIType);
	auto CurrentWidgetClass = InteractionWidgetClasses.Find(UIType);
	if (!CurrentUIInfo->Widget && CurrentWidgetClass)
	{
		CurrentUIInfo->Widget = CreateWidget<UUserWidget>(this, *CurrentWidgetClass);
		if (CurrentUIInfo->Widget)
		{
			CurrentUIInfo->Widget->AddToViewport();
		}
		CurrentUIInfo->TargetActor = TargetActor;
		CurrentUIInfo->bCanInteract = true;
	}
}

void ATPSPlayerController::HideInteractionUI(EInteractionUIType UIType, AActor* TargetActor)
{
	if (!IsLocalController()) return;

	auto CurrentUIInfo = InteractionUIManager.Find(UIType);
	auto CurrentWidgetClass = InteractionWidgetClasses.Find(UIType);
	if (CurrentUIInfo->Widget)
	{
		if (CurrentUIInfo->Widget)
		{
			CurrentUIInfo->Widget->RemoveFromParent();
			CurrentUIInfo->Widget = nullptr;
		}
		CurrentUIInfo->TargetActor = nullptr;
		CurrentUIInfo->bCanInteract = false;
	}
}
