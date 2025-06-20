// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_StartUltimate.h"
#include "Interface/TPSPlayableAnimationInterface.h"
#include "AnimNotify_StartUltimate.h"

void UAnimNotify_StartUltimate::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		ITPSPlayableAnimationInterface* AttackPawn = Cast<ITPSPlayableAnimationInterface>(MeshComp->GetOwner());
		{
			if (AttackPawn)
			{
				AttackPawn->StartUltimate();
			}
		}
	}
}
