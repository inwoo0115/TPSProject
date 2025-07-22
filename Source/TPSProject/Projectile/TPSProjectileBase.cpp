// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ATPSProjectileBase::ATPSProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 설정
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// 기본 발사체 컴포넌트 설정
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 2000.f;
	Movement->MaxSpeed = 2000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.0f;

	// 리플리케이션 설정
	bReplicates = false;
}

// Called when the game starts or when spawned
void ATPSProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	// 일정 시간 후 자동 파괴
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


