// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSRifleBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

ATPSRifleBullet::ATPSRifleBullet()
{
	// 콜리전 설정
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// 기본 발사체 컴포넌트 설정
	Movement->InitialSpeed = 5000.f;
	Movement->MaxSpeed = 5000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.0f;

	// 기본 메쉬 설정 (구체)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (BulletMeshAsset.Object)
	{
		Mesh->SetStaticMesh(BulletMeshAsset.Object);
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetCollisionProfileName("NoCollision");
	}
}

void ATPSRifleBullet::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ATPSRifleBullet::OnHit);

	ResetProjectile();

}

void ATPSRifleBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 충돌 시 파괴
	// Destroy();
}
