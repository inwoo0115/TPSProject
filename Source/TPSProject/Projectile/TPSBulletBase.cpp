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

void ATPSBulletBase::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ATPSBulletBase::OnHit);

	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);
}

void ATPSBulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		auto OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn)
		{
			// �浹 �� ������ ó��
			UGameplayStatics::ApplyDamage(
				OtherActor,
				Damage,
				OwnerPawn->GetController(),
				this,
				UDamageType::StaticClass()
			);
		}

		// �浹 �� �̺�Ʈ ȣ��
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
	
	Destroy(); // �浹 �� �߻�ü �ı�
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
		// �� ������ ���ʿ��Դ� ���ø����̼� ���� ����
		return PawnOwner->GetController() != RealViewer;
	}

	return true;
}