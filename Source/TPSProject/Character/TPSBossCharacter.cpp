// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSBossCharacter.h"
#include "Animation/TPSAnimMontageData.h"
#include "AI/TPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Projectile/TPSHommingMissile.h"
#include "Summons/TPSSkillRangeDecalBase.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"
#include "Net/UnrealNetwork.h"

ATPSBossCharacter::ATPSBossCharacter(const FObjectInitializer& ObjectInitializer)
{
	CharacterName = FText::FromString(TEXT("Strong Robot"));

	CurrentHp = 800.0f;

	MaxHp = 800.0f;

	// AnimMontage Date 설정
	static ConstructorHelpers::FObjectFinder<UTPSAnimMontageData> AnimMontageDataRef(TEXT("/Game/TPSProject/AnimMontageData/BossAnimMontageData.BossAnimMontageData"));
	if (AnimMontageDataRef.Object)
	{
		AnimMontageData = AnimMontageDataRef.Object;
	}

	// Projectile 클래스 경로 지정
	static ConstructorHelpers::FClassFinder<ATPSProjectileBase> ProjectileBPClass(TEXT("/Game/TPSProject/Blueprints/Projectile/BP_HomingMissile.BP_HomingMissile_C"));
	if (ProjectileBPClass.Class)
	{
		ProjectileClass = ProjectileBPClass.Class;
	}

	// Decal
	static ConstructorHelpers::FClassFinder<ATPSSkillRangeDecalBase> DecalBPClass(TEXT("/Game/TPSProject/Blueprints/Decal/BP_BossSkillDecal.BP_BossSkillDecal_C"));
	if (DecalBPClass.Class)
	{
		DecalClass = DecalBPClass.Class;
	}
}

void ATPSBossCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SkillCoolTime += DeltaSeconds;
	UltiCoolTime += DeltaSeconds;

	if (HasAuthority())
	{
		AimRotation = GetControlRotation();
	}

	if (CurrentHp <= 0.0f && !bIsDead)
	{
		ATPSAIController* AICon = Cast<ATPSAIController>(GetController());
		if (AICon)
		{
			AICon->StopBehaviorTree();
			MulticastRPCDead();
		}
	}

	if (SkillDecal)
	{
		UltiElapsedTime += DeltaSeconds;
		float Alpha = FMath::Clamp(UltiElapsedTime / 1.5f, 0.f, 1.f);
		float CurrentScale = FMath::Lerp(0.0f, 2000.0f, Alpha);
		SkillDecal->RangeDecal->DecalSize = FVector(1.0f, 50.0f, CurrentScale);
		
		FVector NewLocation = GetActorLocation() + FRotator(0, SkillDecal->GetActorRotation().Yaw, 0).Vector() * (500.f + (CurrentScale * 0.5f)) + FVector(0.0f, 0.0f, -250.0f);
		SkillDecal->SetActorLocation(NewLocation);
		EffectSpawnRotation = FRotator(0.f, AimRotation.Yaw, 0.f);
		SkillDecal->SetActorRotation(EffectSpawnRotation);
		
		SkillDecal->RangeDecal->MarkRenderStateDirty();
		
		if (UltiElapsedTime >= 1.5f)
		{
			SkillDecal->RangeDecal->SetVisibility(false);
			SkillDecal->Destroy();
			SkillDecal = nullptr;
			UltiElapsedTime = 0.0f;
		}
	}
}

void ATPSBossCharacter::CastSkill()
{
	AAIController* AICon = Cast<AAIController>(GetController());
	AActor* TargetActor = nullptr;
	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComponent();
		if (BlackboardComp)
		{
			TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));

		}
	}

	MulticastRPCCastSkill(TargetActor);
}

void ATPSBossCharacter::CastUlti()
{
	MulticastRPCCastUlti();
}

float ATPSBossCharacter::GetSkillCoolTime()
{
	return SkillCoolTime;
}

float ATPSBossCharacter::GetUltiCoolTime()
{
	return UltiCoolTime;
}

bool ATPSBossCharacter::GetIsDead()
{
	return bIsDead;
}

void ATPSBossCharacter::SpawnExplosion()
{
	if (ExplosionEffect)
	{
		FVector BossLocation = GetActorLocation();

		float StepDistance = 400.f;

		for (int i = 1; i <= 8; i++)
		{
			FVector SpawnLocation = BossLocation + EffectSpawnRotation.Vector() * (StepDistance * i);
			SpawnLocation.Z += 200.f;

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				ExplosionEffect,
				SpawnLocation,
				FRotator(0.0f, 0.0f, 0.0f)
			);
		}


		FVector HalfExtents(3000.f * 0.5f, 300.f * 0.5f, 300.f * 0.5f);
		FVector BoxCenter = BossLocation + EffectSpawnRotation.Vector() * HalfExtents.X;

		TArray<FOverlapResult> Overlaps;
		FCollisionShape CollisionBox = FCollisionShape::MakeBox(HalfExtents);

		bool bHit = GetWorld()->OverlapMultiByChannel(
			Overlaps,
			BoxCenter,
			EffectSpawnRotation.Quaternion(),
			ECC_Pawn,
			CollisionBox
		);

		for (auto& Result : Overlaps)
		{
			AActor* HitActor = Result.GetActor();
			if (HitActor && HitActor != this)
			{
				UGameplayStatics::ApplyDamage(HitActor, 50.f, GetController(), this, UDamageType::StaticClass());
			}
		}

		//DrawDebugBox(
		//	GetWorld(),
		//	BoxCenter,
		//	HalfExtents,
		//	EffectSpawnRotation.Quaternion(),
		//	FColor::Green,
		//	false,      // 지속 여부
		//	5.f,        // 지속 시간
		//	0,
		//	5.f         // 선 두께
		//);
	}
}

void ATPSBossCharacter::MulticastRPCDead_Implementation()
{
	bIsDead = true;
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::LevelEnd]);
}

void ATPSBossCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSBossCharacter, AimRotation);
	DOREPLIFETIME(ATPSBossCharacter, SkillDecal);
}


void ATPSBossCharacter::MulticastRPCStart_Implementation()
{
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::LevelStart]);
}

void ATPSBossCharacter::MulticastRPCCastSkill_Implementation(AActor* Target)
{
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::SkillCast]);
	SkillCoolTime = 0.0f;

	// 발사체 소환
	if (!ProjectileClass)
	{
		return;
	}

	FVector SocketLocation = GetMesh()->GetSocketLocation(TEXT("head"));

	FVector BoxExtent = FVector(40.f, 40.f, 40.f);
	FVector BoxCenter = SocketLocation + FVector(0.0f, 0.0f, 100.0f);

	TArray<FVector> SpawnLocations;

	for (int i = 0; i < 4; i++)
	{
		FVector RandOffset = FVector(
			FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
			FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
			FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
		);
		SpawnLocations.Add(BoxCenter + RandOffset);
	}

	for (const FVector SpawnLocation : SpawnLocations)
	{
		FRotator SpawnRotation = (SpawnLocation - GetActorLocation()).Rotation();
	
		FActorSpawnParameters SpawnParams;

		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ATPSHommingMissile* Projectile = GetWorld()->SpawnActor<ATPSHommingMissile>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);


		if (Projectile)
		{
			if (Target)
			{
				Projectile->SetHomingTarget(Target->GetRootComponent());
			}
		}
	}
}

void ATPSBossCharacter::MulticastRPCCastUlti_Implementation()
{
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::UltiCast]);
	UltiCoolTime = 0.0f;
	FVector SpawnLocation = GetActorLocation() + FRotator(0, AimRotation.Yaw, 0).Vector() * 100.f + FVector(0.0f, 0.0f, -250.0f);
	EffectSpawnRotation = FRotator(0.f, AimRotation.Yaw, 0.f);

	SkillDecal = GetWorld()->SpawnActor<ATPSSkillRangeDecalBase>(
		DecalClass,
		SpawnLocation,
		EffectSpawnRotation
	);
	SkillDecal->RangeDecal->DecalSize = FVector(500.0f, 50.0f, 0.0f);
	SkillDecal->RangeDecal->MarkRenderStateDirty();
}
