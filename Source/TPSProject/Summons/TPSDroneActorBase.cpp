// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSDroneActorBase.h"
#include "Components/SphereComponent.h"

// Sets default values
ATPSDroneActorBase::ATPSDroneActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 콜리전 설정
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = Collision;

	// 기본 메쉬 설정 (구체)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");

	// 리플리케이션 설정
	this->SetReplicates(true);
}

// Called when the game starts or when spawned
void ATPSDroneActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->SetVisibility(false);

		// 소환 되고 위로 이동
		StartLocation = GetActorLocation();
		TargetLocation = StartLocation + FVector(0.f, 0.f, 300.f); // Z축으로 3m 위

		RiseElapsedTime = 0.0f;
		bIsRising = true;
	}

	// 일정 시간 후 자동 파괴
	SetLifeSpan(LifeTime);
	
}

// Called every frame
void ATPSDroneActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRising)
	{
		RiseElapsedTime += DeltaTime;
		float Alpha = FMath::Clamp(RiseElapsedTime / RiseDuration, 0.f, 1.f);

		FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);
		SetActorLocation(NewLocation);

		if (Alpha >= 1.f)
		{
			bIsRising = false;

			if (Mesh)
			{
				Mesh->SetVisibility(true);
			}
		}
	}
}

bool ATPSDroneActorBase::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (!GetOwner())
	{
		return true;
	}

	// 이 액터의 오너에게는 리플리케이션 되지 않음
	return RealViewer != GetOwner();
}

