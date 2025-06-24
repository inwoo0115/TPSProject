// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSUltimateActorBase.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATPSUltimateActorBase::ATPSUltimateActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 설정
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("OverlapAllDynamic");
	Collision->SetGenerateOverlapEvents(true);
	RootComponent = Collision;

	// 리플리케이션 설정
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATPSUltimateActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 일정 시간 후 자동 파괴
	SetLifeSpan(LifeTime);
}

void ATPSUltimateActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 파괴될 때 별도의 DeathEffect 나이아가라 호출
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

		if (HasAuthority())
		{
			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				Damage,
				GetActorLocation(),
				500,
				nullptr,               // 기본 DamageType
				TArray<AActor*>(),     // 무시할 액터들
				GetOwner(),
				GetOwner()->GetInstigatorController(),
				true,
				ECC_Pawn
			);
		}
	}
}

// Called every frame
void ATPSUltimateActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

