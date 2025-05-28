// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interface/TPSInteractableInterface.h"
#include "TPSInteractionObjectBase.generated.h"

UCLASS()
class TPSPROJECT_API ATPSInteractionObjectBase : public AActor, public ITPSInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSInteractionObjectBase();

	// ��ȣ �ۿ� ������Ʈ �� interaction ���� �Լ�
	virtual void Interact(APlayerController* PC) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> InteractionBox;

	// ������ �̺�Ʈ �Լ�
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
