// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/TPSInteractionObjectBase.h"
#include "TPSOnlineInteractionObjectBase.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSOnlineInteractionObjectBase : public ATPSInteractionObjectBase
{
	GENERATED_BODY()

public:
	ATPSOnlineInteractionObjectBase();

	// 상호 작용 오브젝트 별 interaction 가상 함수
	virtual void Interact(APlayerController* PC) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
