// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSBasicDroneActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ATPSBasicDroneActor::ATPSBasicDroneActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (MeshAsset.Object)
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}
