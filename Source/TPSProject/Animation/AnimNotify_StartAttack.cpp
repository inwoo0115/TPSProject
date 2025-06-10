// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_StartAttack.h"
#include "Interface/TPSPlayableAnimationInterface.h"

void UAnimNotify_StartAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ITPSPlayableAnimationInterface* AttackPawn = Cast<ITPSPlayableAnimationInterface>(MeshComp->GetOwner());
		{
			if (AttackPawn)
			{
				AttackPawn->StartAttack();
			}
		}
	}
}
