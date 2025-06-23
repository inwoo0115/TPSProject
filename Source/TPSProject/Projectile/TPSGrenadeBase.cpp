// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSGrenadeBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


ATPSGrenadeBase::ATPSGrenadeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ����
	Collision->InitSphereRadius(2.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// �⺻ �߻�ü ������Ʈ ����
	Movement->InitialSpeed = 3000.f;
	Movement->MaxSpeed = 3000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 1.0f;

	// �⺻ �޽� ���� (��ü)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (BulletMeshAsset.Object)
	{
		Mesh->SetStaticMesh(BulletMeshAsset.Object);
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetCollisionProfileName("NoCollision");
	}

	LifeTime = 20.0f;
}

void ATPSGrenadeBase::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ATPSGrenadeBase::OnHit);

	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);
}

void ATPSGrenadeBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	MulticastRPCExplosionEffect();

	if (HasAuthority())
	{
		// �浹 �� ���� �ݰ� ������ ó��
		UGameplayStatics::ApplyRadialDamage(
			GetWorld(),
			Damage,             // ������ ��ġ
			GetActorLocation(),          // ���� ����
			ExplosionRadius,             // ���� �ݰ�
			UDamageType::StaticClass(),// ������Ÿ��(������ UDamageType::StaticClass())
			TArray<AActor*>(),           // ������ ���͵�
			this,                        // ������ ������
			GetInstigatorController(),   // Instigator ��Ʈ�ѷ�
			true, // ���� ������ ���
			ECC_Pawn
		);



		// �浹 �� �̺�Ʈ ȣ��
		auto Event = Cast<ITPSEventComponentInterface>(GetOwner());
		if (Event)
		{
			Event->GetEventComponent()->OnSpAttackHitEvent.Broadcast(GetActorLocation());
		}
	}
	// �浹 �� �ı�
	Destroy();
}

void ATPSGrenadeBase::MulticastRPCExplosionEffect_Implementation()
{
	// �ı��� �� ������ DeathEffect ���̾ư��� ȣ��
	if (ExplosionEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			ExplosionEffect,
			GetActorLocation(),
			GetActorRotation(),
			FVector(1.f),
			true,
			true
		);
	}
}
