// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSCharacterMovementComponent.h"
#include "TPSCharacterMovementComponent.h"
#include "GameFramework/Character.h"

UTPSCharacterMovementComponent::UTPSCharacterMovementComponent()
{
    bIsRopeAttached = false;
    RopeLocation = FVector::ZeroVector;
}

void UTPSCharacterMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
    switch (CustomMovementMode)
    {
    case (uint8)ECustomMovementMode::CMOVE_Rope:
        PhysRope(DeltaTime, Iterations);
        break;
    default:
        Super::PhysCustom(DeltaTime, Iterations);
        break;
    }
}

void UTPSCharacterMovementComponent::PhysRope(float DeltaTime, int32 Iterations)
{
    if (!CharacterOwner)
        return;

    // ���ӵ� ���
    CurrentVelocity = Velocity;
    CurrentAcceleration = (CurrentVelocity - LastVelocity) / DeltaTime;
    LastVelocity = CurrentVelocity;

    // �߷� ����
    FVector GravityVec = FVector(0.f, 0.f, GetGravityZ()) * DeltaTime;
    Velocity += GravityVec;

    // ĳ���� �Ӹ� ��ġ (�Ŵ޸��� ������)
    const FVector HeadLocation = CharacterOwner->GetMesh()->GetSocketLocation(TEXT("head"));

    FVector RopeDir = RopeLocation - HeadLocation;
    float RopeLength = RopeDir.Size();

    if (RopeLength > 200.f)
    {
        RopeDir.Normalize();

        // �߷� ����
        const FVector Gravity = FVector(0.f, 0.f, GetGravityZ());

        // ��� ���
        double DotAcc = RopeDir | CurrentAcceleration;
        double DotGrav = RopeDir | Gravity;

        double ForceScalar = 0.0;
        if (DotAcc < 0.0)  ForceScalar += DotAcc;
        if (DotGrav < 0.0) ForceScalar += DotGrav;

        ForceScalar *= -1.0 * Mass;

        // ź����
        double ElasticForce = (RopeLength > 100.f) ? RopeLength * 80.0 : 0.0;

        // ���� ��
        FVector AddForce = (ForceScalar + ElasticForce) * RopeDir;

        // �ӵ� ����
        Velocity += (AddForce / Mass) * DeltaTime;
    }

    // �̵� ó��
    FVector Delta = Velocity * DeltaTime;
    FHitResult Hit;
    SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);
}

void UTPSCharacterMovementComponent::StartRope(const FVector& InRopeLocation)
{
    bIsRopeAttached = true;
    RopeLocation = InRopeLocation;

    SetMovementMode(MOVE_Custom, (uint8)ECustomMovementMode::CMOVE_Rope);
}

void UTPSCharacterMovementComponent::StopRope()
{
    bIsRopeAttached = false;

    // ���� ���� �� ���Ϸ� ��ȯ
    SetMovementMode(MOVE_Falling);
}
