// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TPSHommingMissile.h"
#include "TPSHommingMissile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"
#include "Interface/TPSEventComponentInterface.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

ATPSHommingMissile::ATPSHommingMissile()
{
	PrimaryActorTick.bCanEverTick = true;
	// 콜리전 설정
	Collision->InitSphereRadius(5.0f);
	Collision->SetCollisionProfileName("ProjectileProfile");
	RootComponent = Collision;

	// 기본 발사체 컴포넌트 설정
	Movement->InitialSpeed = 1000.f;
	Movement->MaxSpeed = 2000.f;
	Movement->bRotationFollowsVelocity = true;
	Movement->ProjectileGravityScale = 0.0f;
	Movement->bIsHomingProjectile = false;
	Movement->HomingAccelerationMagnitude = 5000.f; // 추적 민감도

	// 리플리케이션 설정
	bReplicates = true;
}

void ATPSHommingMissile::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ATPSHommingMissile::OnHit);
	Collision->IgnoreActorWhenMoving(GetOwner(), true);

	RandomCurveOffset = FMath::VRand() * CurveStrength;
	GetWorldTimerManager().SetTimer(CurveTimerHandle, this, &ATPSHommingMissile::ApplyRandomCurve, 0.02f, true);

	// 일정 시간 후 유도 활성화
	GetWorldTimerManager().SetTimer(HomingTimerHandle, this, &ATPSHommingMissile::EnableHoming, 1.0f, false);

	// 일정 시간 후 유도 해제
	GetWorldTimerManager().SetTimer(DisableHomingTimerHandle, this, &ATPSHommingMissile::DisableHoming, 5.0f, false);


	// 일정 시간 후 자동 파괴
	SetLifeSpan(10.0f);
}

void ATPSHommingMissile::SetHomingTarget(USceneComponent* Target)
{
	if (Target)
	{
		TargetComponent = Target;
	}
}

void ATPSHommingMissile::ApplyRandomCurve()
{
	if (!Movement) return;

	// 초기 방향 + 랜덤 오프셋 적용
	FVector NewVelocity = Movement->Velocity + RandomCurveOffset * 0.2f; // delta time scaling
	NewVelocity = NewVelocity.GetClampedToMaxSize(Movement->MaxSpeed);
	Movement->Velocity = NewVelocity;

	// CurveDuration 경과 후 타이머 종료
	CurveDuration -= 0.02f;
	if (CurveDuration <= 0.f)
	{
		GetWorldTimerManager().ClearTimer(CurveTimerHandle);
	}
}

void ATPSHommingMissile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

bool ATPSHommingMissile::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
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

void ATPSHommingMissile::EnableHoming()
{
	if (TargetComponent && Movement)
	{
		Movement->bIsHomingProjectile = true;
		Movement->HomingTargetComponent = TargetComponent;
	}
}

void ATPSHommingMissile::DisableHoming()
{
	if (TargetComponent && Movement)
	{
		Movement->bIsHomingProjectile = false;
		Movement->HomingTargetComponent = nullptr;
	}
}
