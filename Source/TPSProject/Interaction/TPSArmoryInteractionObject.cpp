// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSArmoryInteractionObject.h"
#include "GameInstance/TPSUiSubsystem.h"

ATPSArmoryInteractionObject::ATPSArmoryInteractionObject()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmoryMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ObjectMesh.Object)
	{
		StaticMesh->SetStaticMesh(ObjectMesh.Object);
	}
}

void ATPSArmoryInteractionObject::Interact(APlayerController* PC)
{
	auto* UISubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UISubsystem)
	{
		UISubsystem->ShowUI(EUIType::Ability);
	}
}
