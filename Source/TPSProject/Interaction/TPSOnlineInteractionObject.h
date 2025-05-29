// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/TPSInteractionObjectBase.h"
#include "TPSOnlineInteractionObject.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API ATPSOnlineInteractionObject : public ATPSInteractionObjectBase
{
	GENERATED_BODY()
public:
	ATPSOnlineInteractionObject();

	// ��ȣ �ۿ� ������Ʈ �� interaction ���� �Լ�
	virtual void Interact(APlayerController* PC) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
