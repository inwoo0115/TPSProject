// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSBossCharacter.h"
#include "Animation/TPSAnimMontageData.h"
#include "AI/TPSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Projectile/TPSHommingMissile.h"
#include "Summons/TPSSkillRangeDecalBase.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"

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

	if (CurrentHp <= 0.0f && !bIsDead)
	{
		ATPSAIController* AICon = Cast<ATPSAIController>(GetController());
		if (AICon)
		{
			AICon->StopBehaviorTree();
			bIsDead = true;
			PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::LevelEnd]);
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
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::SkillCast]);
	SkillCoolTime = 0.0f;

	// 발사체 소환
	if (!ProjectileClass)
	{
		return;
	}

	FVector SocketLocation = GetMesh()->GetSocketLocation(TEXT("head"));

	FVector BoxExtent = FVector(30.f, 30.f, 30.f);
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

	for (FVector SpawnLocation : SpawnLocations)
	{
		FRotator SpawnRotation = FRotator(0, 0, 0);

		// 총알 스폰
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
			AAIController* AICon = Cast<AAIController>(GetController());
			if (AICon)
			{
				UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComponent();
				if (BlackboardComp)
				{
					AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
					Projectile->SetHomingTarget(TargetActor->GetRootComponent());
				}
			}
		}
	}
}

void ATPSBossCharacter::CastUlti()
{
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::UltiCast]);
	UltiCoolTime = 0.0f;
	FVector SpawnLocation = GetActorLocation() + FRotator(0, GetControlRotation().Yaw, 0).Vector() * 100.f + FVector(0.0f, 0.0f, -250.0f);
	EffectSpawnRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);

	SkillDecal = GetWorld()->SpawnActor<ATPSSkillRangeDecalBase>(
		DecalClass,
		SpawnLocation,
		EffectSpawnRotation
	);
	SkillDecal->RangeDecal->DecalSize = FVector(1.0f, 50.0f, 0.0f);
	SkillDecal->RangeDecal->MarkRenderStateDirty();
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
	}
}
