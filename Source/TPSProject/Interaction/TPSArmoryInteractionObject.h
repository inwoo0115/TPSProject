// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/TPSInteractionObjectBase.h"
#include "TPSArmoryInteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSArmoryInteractionObject : public ATPSInteractionObjectBase
{
	GENERATED_BODY()
	
public:
	ATPSArmoryInteractionObject();

	virtual void Interact(APlayerController* PC) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
