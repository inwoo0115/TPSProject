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

	virtual void OnRegister() override;

	virtual void BeginPlay() override;

	// Setter
	UFUNCTION(BlueprintCallable, Category = "RopeComponent")
	void SetRopeLocation(const FVector& NewLocation);


	UFUNCTION(BlueprintCallable, Category = "RopeComponent")
	void SetIsGrappling(const bool NewIsGrappling);

	// Getter
	UFUNCTION(BlueprintCallable, Category = "RopeComponent")
	bool GetIsGrappling();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	TObjectPtr<class ACharacter> Owner;

	FVector3d RopeLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	FVector LastVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	FVector CurrentAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
	bool IsGrappling = false;

};
