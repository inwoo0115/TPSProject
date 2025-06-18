// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSBasicDroneActor.h"
#include "Components/SphereComponent.h"

// Sets default values
ATPSBasicDroneActor::ATPSBasicDroneActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (BulletMeshAsset.Object)
	{
		Mesh->SetStaticMesh(BulletMeshAsset.Object);
	}
}
