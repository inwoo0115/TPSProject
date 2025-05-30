// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/TPSSpInteractionObjectBase.h"
#include "TPSSpInteractionRopeActionObject.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSSpInteractionRopeActionObject : public ATPSSpInteractionObjectBase
{
	GENERATED_BODY()

public:
	ATPSSpInteractionRopeActionObject();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
