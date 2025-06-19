// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TPSProjectilePoolManager.h"

// Sets default values
ATPSProjectileBase::ATPSProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	Movement->bAutoActivate = false;


	// 리플리케이션 설정
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATPSProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	ResetProjectile();
}


void ATPSProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 충돌 시 처리 등록


}

void ATPSProjectileBase::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

void ATPSProjectileBase::FireInDirection(const FVector& Direction)
{
	Movement->Velocity = Direction * Movement->InitialSpeed;
	GetWorld()->GetTimerManager().SetTimer(LifeSpanHandle, this, &ATPSProjectileBase::OnLifeSpanExpired, LifeTime, false);

}

void ATPSProjectileBase::FireInLocal(const FVector& SpawnLocation, const FVector& Direction, const FRotator& Rotation)
{
	SetActorTickEnabled(true);
	SetActorRotation(Rotation);
	SetActorLocation(SpawnLocation);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	Movement->Activate();
	FireInDirection(Direction);
}


void ATPSProjectileBase::ResetProjectile()
{
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	Movement->StopMovementImmediately();
	GetWorld()->GetTimerManager().ClearTimer(LifeSpanHandle);
	Movement->Deactivate();
	SetActorTickEnabled(false);
}

void ATPSProjectileBase::OnLifeSpanExpired()
{
	ResetProjectile();

	if (PoolOwner)
	{
		class ATPSProjectilePoolManager* Pool = Cast<ATPSProjectilePoolManager>(PoolOwner);
		if (Pool)
		{
			Pool->ReturnProjectile(this);
		}
	}
}

void ATPSProjectileBase::MulticastRPCActivate_Implementation(const FVector& SpawnLocation, const FVector& Direction, const FRotator& Rotation)
{
	SetActorTickEnabled(true);
	SetActorRotation(Rotation);
	SetActorLocation(SpawnLocation);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	Movement->Activate();
	FireInDirection(Direction);
}

