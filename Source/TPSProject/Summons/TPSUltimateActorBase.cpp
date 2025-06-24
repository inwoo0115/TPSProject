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

	// �ݸ��� ����
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("OverlapAllDynamic");
	Collision->SetGenerateOverlapEvents(true);
	RootComponent = Collision;

	// ���ø����̼� ����
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATPSUltimateActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);
}

void ATPSUltimateActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

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

		if (HasAuthority())
		{
			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				Damage,
				GetActorLocation(),
				500,
				nullptr,               // �⺻ DamageType
				TArray<AActor*>(),     // ������ ���͵�
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

