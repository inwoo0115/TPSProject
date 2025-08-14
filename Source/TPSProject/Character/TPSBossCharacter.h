// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TPSNonCharacterBase.h"
#include "TPSBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSBossCharacter : public ATPSNonCharacterBase
{
	GENERATED_BODY()
	
public:
	ATPSBossCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaSeconds) override;

	void CastSkill();

	void CastUlti();

	float GetSkillCoolTime();

	float GetUltiCoolTime();

	// AnimMontage 데이터 에셋
	UPROPERTY(EditAnywhere, Category = AnimMontage)
	TObjectPtr<class UTPSAnimMontageData> AnimMontageData;

	bool GetIsDead();

protected:
	float SkillCoolTime = 5.0f;
	float UltiCoolTime = 5.0f;

	bool bIsDead = false;
};
