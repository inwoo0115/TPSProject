// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterComponent/TPSRopeActionComponent.h"
#include "TPSRopeActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UTPSRopeActionComponent::UTPSRopeActionComponent()
{
	// ĳ����, ĳ���� �����Ʈ ����
	Owner = Cast<ACharacter>(GetOwner());
	//���͸��� ����
	static ConstructorHelpers::FObjectFinder<UMaterial> CableMaterial(TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));
	if (CableMaterial.Object)
	{
		SetMaterial(0, CableMaterial.Object);
	}

	// ���̺� ���� �ʱ�ȭ
	RopeLocation = FVector(0.0f, 0.0f, 0.0f);
	SolverIterations = 16;
	bEnableStiffness = true;
	CableLength = 10;
	EndLocation = FVector(0.0f, 0.0f, 0.0f);
	SetVisibility(true);
	CableWidth = 3.0f;

	// ���ø����̼� ����
	SetIsReplicatedByDefault(true);
}


void UTPSRopeActionComponent::OnRegister()
{
	Super::OnRegister();
	//���̺� ����
	AttachToComponent(Owner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Muzzle_03"));
}

void UTPSRopeActionComponent::BeginPlay()
{
	Super::BeginPlay();
	//���� �� ��Ȱ��ȭ
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
