// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPSCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class ECustomMovementMode : uint8
{
    CMOVE_None UMETA(DisplayName = "None"),
    CMOVE_Rope UMETA(DisplayName = "Rope"),
};

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
    UTPSCharacterMovementComponent();

    virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
    void PhysRope(float DeltaTime, int32 Iterations);

    void StartRope(const FVector& InRopeLocation);
    void StopRope();

    FVector RopeLocation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
    bool bIsRopeAttached;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
    FVector LastVelocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
    FVector CurrentVelocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rope")
    FVector CurrentAcceleration;
};
