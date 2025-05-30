// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CableComponent.h"
#include "TPSRopeActionComponent.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSRopeActionComponent : public UCableComponent
{
	GENERATED_BODY()
	
public:
	UTPSRopeActionComponent();

	void UpdateTension();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnRegister() override;

	virtual void BeginPlay() override;

	// Setter
	UFUNCTION(BlueprintCallable, Category = "RopeComponent")
	FORCEINLINE void SetRopeLocation(const FVector& NewLocation);


	UFUNCTION(BlueprintCallable, Category = "RopeComponent")
	void SetIsGrappling(const bool NewIsGrappling);

	// Getter
	UFUNCTION(BlueprintCallable, Category = "RopeComponent")
	FORCEINLINE bool GetIsGrappling();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	FVector3d RopeLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	FVector LastVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	FVector CurrentAcceleration;

	bool IsGrappling = false;
};
