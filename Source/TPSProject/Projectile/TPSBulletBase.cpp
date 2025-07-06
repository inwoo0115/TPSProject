// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSBulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


ATPSBulletBase::ATPSBulletBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 설정
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// 기본 발사체 컴포넌트 설정
	Movement->InitialSpeed = 10000.f;
	Movement->MaxSpeed = 10000.f;
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

void ATPSBulletBase::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ATPSBulletBase::OnHit);

	// 일정 시간 후 자동 파괴
	SetLifeSpan(LifeTime);
}

void ATPSBulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		auto OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn)
		{
			// 충돌 시 데미지 처리
			UGameplayStatics::ApplyDamage(
				OtherActor,
				Damage,
				OwnerPawn->GetController(),
				this,
				UDamageType::StaticClass()
			);
		}

		// 충돌 시 이벤트 호출
		auto Event = Cast<ITPSEventComponentInterface>(GetOwner());
		if (Event)
		{
			Event->GetEventComponent()->OnAttackHitEvent.Broadcast(GetActorLocation());
		}
	}

	if (ExplosionEffect)
	{
		FRotator EffectRotation = GetActorRotation();
		EffectRotation.Pitch += 90;

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ExplosionEffect,
			GetActorLocation(),
			EffectRotation,
			FVector(1.f),
			true,
			true
		);
	}
	
	Destroy(); // 충돌 시 발사체 파괴
}


bool ATPSBulletBase::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (!GetOwner())
	{
		return true;
	}

	auto PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner)
	{
		// 이 액터의 오너에게는 리플리케이션 되지 않음
		return PawnOwner->GetController() != RealViewer;
	}

	return true;
}