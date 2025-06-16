// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSGrenade.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"

ATPSGrenade::ATPSGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ����
	Collision->InitSphereRadius(2.0f);
	Collision->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Collision;

	// �⺻ �߻�ü ������Ʈ ����
	Movement->InitialSpeed = 2400.f;
	Movement->MaxSpeed = 2400.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 1.0f;

	// �⺻ �޽� ���� (��ü)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BulletMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (BulletMeshAsset.Object)
	{
		Mesh->SetStaticMesh(BulletMeshAsset.Object);
		Mesh->SetupAttachment(RootComponent);
	}

}

void ATPSGrenade::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ATPSGrenade::OnHit);

	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);
}

void ATPSGrenade::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		// �������� �浹 �̺�Ʈ ����
		//GetGameInstance()->GetSubsystem<UTPSGameplayEventSubsystem>()->BroadcastHitEvent();
	}

	// �浹 �� �ı�
	Destroy();
}
