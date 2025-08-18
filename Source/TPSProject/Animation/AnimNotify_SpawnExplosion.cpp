// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SpawnExplosion.h"
#include "AnimNotify_SpawnExplosion.h"
#include "Character/TPSBossCharacter.h"

void UAnimNotify_SpawnExplosion::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ATPSBossCharacter* AttackPawn = Cast<ATPSBossCharacter>(MeshComp->GetOwner());
		{
			if (AttackPawn)
			{
				AttackPawn->SpawnExplosion();
			}
		}
	}
}
