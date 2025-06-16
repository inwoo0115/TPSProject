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

	// 콜리전 설정
	Collision->InitSphereRadius(2.0f);
	Collision->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = Collision;

	// 기본 발사체 컴포넌트 설정
	Movement->InitialSpeed = 2400.f;
	Movement->MaxSpeed = 2400.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 1.0f;

	// 기본 메쉬 설정 (구체)
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

	// 일정 시간 후 자동 파괴
	SetLifeSpan(LifeTime);
}

void ATPSGrenade::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		// 서버에서 충돌 이벤트 관리
		//GetGameInstance()->GetSubsystem<UTPSGameplayEventSubsystem>()->BroadcastHitEvent();
	}

	// 충돌 시 파괴
	Destroy();
}
