// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TPSEventComponentInterface.generated.h"

class UTPSGameplayEventComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTPSEventComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TPSPROJECT_API ITPSEventComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UTPSGameplayEventComponent* GetEventComponent() = 0;
};
