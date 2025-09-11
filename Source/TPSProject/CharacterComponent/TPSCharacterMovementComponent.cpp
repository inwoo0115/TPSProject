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

    // 가속도 계산
    CurrentVelocity = Velocity;
    CurrentAcceleration = (CurrentVelocity - LastVelocity) / DeltaTime;
    LastVelocity = CurrentVelocity;

    // 중력 적용
    FVector GravityVec = FVector(0.f, 0.f, GetGravityZ()) * DeltaTime;
    Velocity += GravityVec;

    // 캐릭터 머리 위치 (매달리는 기준점)
    const FVector HeadLocation = CharacterOwner->GetMesh()->GetSocketLocation(TEXT("head"));

    FVector RopeDir = RopeLocation - HeadLocation;
    float RopeLength = RopeDir.Size();

    if (RopeLength > 200.f)
    {
        RopeDir.Normalize();

        // 중력 벡터
        const FVector Gravity = FVector(0.f, 0.f, GetGravityZ());

        // 장력 계산
        double DotAcc = RopeDir | CurrentAcceleration;
        double DotGrav = RopeDir | Gravity;

        double ForceScalar = 0.0;
        if (DotAcc < 0.0)  ForceScalar += DotAcc;
        if (DotGrav < 0.0) ForceScalar += DotGrav;

        ForceScalar *= -1.0 * Mass;

        // 탄성력
        double ElasticForce = (RopeLength > 100.f) ? RopeLength * 80.0 : 0.0;

        // 최종 힘
        FVector AddForce = (ForceScalar + ElasticForce) * RopeDir;

        // 속도 갱신
        Velocity += (AddForce / Mass) * DeltaTime;
    }

    // 이동 처리
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

    // 로프 해제 시 낙하로 전환
    SetMovementMode(MOVE_Falling);
}
