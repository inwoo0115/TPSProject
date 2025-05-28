// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSArmoryInteractionObject.h"

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
	UE_LOG(LogTemp, Log, TEXT("Interact success"));
}
