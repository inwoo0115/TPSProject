// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSRifleBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

ATPSRifleBullet::ATPSRifleBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ����
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// �⺻ �߻�ü ������Ʈ ����
	Movement->InitialSpeed = 10000.f;
	Movement->MaxSpeed = 10000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.0f;

	// �⺻ �޽� ���� (��ü)
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

	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);

}

void ATPSRifleBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		auto Event = Cast<ITPSEventComponentInterface>(GetOwner());
		if (Event)
		{
			Event->GetEventComponent()->OnHitEvent.Broadcast();
		}
	}

	Destroy();
}
