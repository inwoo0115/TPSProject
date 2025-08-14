// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSBossCharacter.h"
#include "Animation/TPSAnimMontageData.h"
#include "AI/TPSAIController.h"

ATPSBossCharacter::ATPSBossCharacter(const FObjectInitializer& ObjectInitializer)
{
	CharacterName = FText::FromString(TEXT("Strong Robot"));

	CurrentHp = 800.0f;

	MaxHp = 800.0f;

	// AnimMontage Date ¼³Á¤
	static ConstructorHelpers::FObjectFinder<UTPSAnimMontageData> AnimMontageDataRef(TEXT("/Game/TPSProject/AnimMontageData/BossAnimMontageData.BossAnimMontageData"));
	if (AnimMontageDataRef.Object)
	{
		AnimMontageData = AnimMontageDataRef.Object;
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
}

void ATPSBossCharacter::CastSkill()
{
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::SkillCast]);
	SkillCoolTime = 0.0f;
}

void ATPSBossCharacter::CastUlti()
{
	PlayAnimMontage(AnimMontageData->AnimMontages[EMontageType::UltiCast]);
	UltiCoolTime = 0.0f;
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
