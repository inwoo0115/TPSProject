// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/TPSInteractionObjectBase.h"
#include "TPSInventoryInteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSInventoryInteractionObject : public ATPSInteractionObjectBase
{
	GENERATED_BODY()

public:
	ATPSInventoryInteractionObject();

	virtual void Interact(APlayerController* PC);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
};
