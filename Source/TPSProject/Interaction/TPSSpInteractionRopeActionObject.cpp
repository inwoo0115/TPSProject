// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TPSSpInteractionRopeActionObject.h"
#include "TPSSpInteractionRopeActionObject.h"

ATPSSpInteractionRopeActionObject::ATPSSpInteractionRopeActionObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OnlineMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ObjectMesh.Object)
	{
		StaticMesh->SetStaticMesh(ObjectMesh.Object);
	}
}
