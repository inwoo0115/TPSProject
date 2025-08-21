// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSInventoryInteractionObject.h"
#include "GameInstance/TPSUiSubsystem.h"

ATPSInventoryInteractionObject::ATPSInventoryInteractionObject()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ObjectMesh.Object)
	{
		StaticMesh->SetStaticMesh(ObjectMesh.Object);
	}
}


void ATPSInventoryInteractionObject::Interact(APlayerController* PC)
{
	auto* UISubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UISubsystem)
	{
		UISubsystem->ShowUI(EUIType::Inventory);
	}
}