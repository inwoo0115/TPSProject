// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSRopeActionComponent.h"
#include "TPSRopeActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UTPSRopeActionComponent::UTPSRopeActionComponent()
{
	// 캐릭터, 캐릭터 무브먼트 설정
	Owner = Cast<ACharacter>(GetOwner());
	//머터리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> CableMaterial(TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));
	if (CableMaterial.Object)
	{
		SetMaterial(0, CableMaterial.Object);
	}

	// 케이블 설정 초기화
	RopeLocation = FVector(0.0f, 0.0f, 0.0f);
	SolverIterations = 16;
	bEnableStiffness = true;
	CableLength = 10;
	EndLocation = FVector(0.0f, 0.0f, 0.0f);
	SetVisibility(true);
	CableWidth = 3.0f;

	// 리플리케이션 세팅
	SetIsReplicatedByDefault(true);
}


void UTPSRopeActionComponent::OnRegister()
{
	Super::OnRegister();
	//케이블 부착
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Muzzle_03"));
}

void UTPSRopeActionComponent::BeginPlay()
{
	Super::BeginPlay();
	//시작 시 비활성화
	UnregisterComponent();
}


void UTPSRopeActionComponent::SetRopeLocation(const FVector& NewLocation)
{
	RopeLocation = NewLocation;
}

void UTPSRopeActionComponent::SetIsGrappling(const bool NewIsGrappling)
{
	IsGrappling = NewIsGrappling;
}


bool UTPSRopeActionComponent::GetIsGrappling()
{
	return IsGrappling;
}
