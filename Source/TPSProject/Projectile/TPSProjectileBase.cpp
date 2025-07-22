// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ATPSProjectileBase::ATPSProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ����
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// �⺻ �߻�ü ������Ʈ ����
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 2000.f;
	Movement->MaxSpeed = 2000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.0f;

	// ���ø����̼� ����
	bReplicates = false;
}

// Called when the game starts or when spawned
void ATPSProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);
}


void ATPSProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

float ATPSProjectileBase::GetUltimateGaugeRatio()
{
	return UltiGaugeRatio;
}


