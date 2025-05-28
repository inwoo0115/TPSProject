// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSOnlineInteractionObjectBase.h"
#include "TPSOnlineInteractionObjectBase.h"
#include "GameInstance/TPSUiSubsystem.h"

ATPSOnlineInteractionObjectBase::ATPSOnlineInteractionObjectBase()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OnlineMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ObjectMesh.Object)
	{
		StaticMesh->SetStaticMesh(ObjectMesh.Object);
	}
}

void ATPSOnlineInteractionObjectBase::Interact(APlayerController* PC)
{
	auto* UISubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
	if (UISubsystem)
	{
		UISubsystem->ShowUI(EUIType::Online);
	}
}
