// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSDroneActorBase.h"
#include "Components/SphereComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

// Sets default values
ATPSDroneActorBase::ATPSDroneActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ݸ��� ����
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("OverlapAllDynamic");
	Collision->SetGenerateOverlapEvents(true);
	RootComponent = Collision;

	// �⺻ �޽� ���� (��ü)
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");

	// ���ø����̼� ����
	bReplicates = true;
}

// Called when the game starts or when spawned
void ATPSDroneActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->SetVisibility(false);

		// ��ȯ �ǰ� ���� �̵�
		StartLocation = GetActorLocation();
		TargetLocation = StartLocation + FVector(0.f, 0.f, 300.f); // Z������ 3m ��

		RiseElapsedTime = 0.0f;
		bIsRising = true;
	}

	// 0.5�ʸ��� CheckOverlaps ȣ��
	GetWorld()->GetTimerManager().SetTimer(OverlapCheckTimerHandle, this, &ATPSDroneActorBase::CheckOverlaps, 0.5f, true);

	// ���� �ð� �� �ڵ� �ı�
	SetLifeSpan(LifeTime);
	
}

void ATPSDroneActorBase::CheckOverlaps()
{
	TArray<AActor*> OverlappingActors;
	Collision->GetOverlappingActors(OverlappingActors);

	if (HasAuthority())
	{
		for (AActor* OtherActor : OverlappingActors)
		{
			auto EventInterface = Cast<ITPSEventComponentInterface>(OtherActor);
			if (EventInterface && EventInterface->GetEventComponent())
			{
				EventInterface->GetEventComponent()->OnHpChangeEvent.Broadcast(5.0f);
			}
		}
	}
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

	// �� ������ ���ʿ��Դ� ���ø����̼� ���� ����
	return RealViewer != GetOwner();
}

