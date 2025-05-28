// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSInteractionObjectBase.h"
#include "Character/TPSCharacterBase.h"
#include "Components/BoxComponent.h"
#include "Interface/TPSInteractionWidgetInterface.h"

// Sets default values
ATPSInteractionObjectBase::ATPSInteractionObjectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 박스 컴포넌트 설정
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	RootComponent = InteractionBox;
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f)); // 박스 크기 설정
	InteractionBox->SetCollisionProfileName(TEXT("Trigger"));
	InteractionBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATPSInteractionObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ATPSInteractionObjectBase::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ATPSInteractionObjectBase::OnBoxEndOverlap);
}

void ATPSInteractionObjectBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerCharacter = Cast<ATPSCharacterBase>(OtherActor);
	if (PlayerCharacter && PlayerCharacter->GetController())
	{
		if (auto InteractionUIInterface = Cast<ITPSInteractionWidgetInterface>(PlayerCharacter->GetController()))
		{
			InteractionUIInterface->ShowInteractionUI(EInteractionUIType::Default, this);
			InteractionUIInterface->SetCanInteract(EInteractionUIType::Default, true);
		}
	}
}

void ATPSInteractionObjectBase::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto PlayerCharacter = Cast<ATPSCharacterBase>(OtherActor);
	if (PlayerCharacter && PlayerCharacter->GetController())
	{
		if (auto InteractionUIInterface = Cast<ITPSInteractionWidgetInterface>(PlayerCharacter->GetController()))
		{
			InteractionUIInterface->HideInteractionUI(EInteractionUIType::Default, this);
			InteractionUIInterface->SetCanInteract(EInteractionUIType::Default, false);
		}
	}
}

void ATPSInteractionObjectBase::Interact(APlayerController* PC)
{
}
