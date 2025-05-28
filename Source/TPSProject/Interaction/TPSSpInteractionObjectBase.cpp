// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSSpInteractionObjectBase.h"
#include "Interface/TPSInteractionWidgetInterface.h"
#include "Components/BoxComponent.h"

// Sets default values
ATPSSpInteractionObjectBase::ATPSSpInteractionObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 박스 컴포넌트 설정
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpInteractionBox"));
	RootComponent = InteractionBox;
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f)); // 박스 크기 설정
	InteractionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ATPSSpInteractionObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATPSSpInteractionObjectBase::TraceBeginOverlap(AController* PC)
{
	if (auto InteractionUIInterface = Cast<ITPSInteractionWidgetInterface>(PC))
	{
		InteractionUIInterface->ShowInteractionUI(EInteractionUIType::Special, this);
		InteractionUIInterface->SetCanInteract(EInteractionUIType::Special, true);
	}
}

void ATPSSpInteractionObjectBase::TraceEndOverlap(AController* PC)
{
	if (auto InteractionUIInterface = Cast<ITPSInteractionWidgetInterface>(PC))
	{
		InteractionUIInterface->HideInteractionUI(EInteractionUIType::Special, this);
		InteractionUIInterface->SetCanInteract(EInteractionUIType::Special, false);
	}
}
