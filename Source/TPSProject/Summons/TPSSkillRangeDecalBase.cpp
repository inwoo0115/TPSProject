// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSSkillRangeDecalBase.h"
#include "Components/DecalComponent.h"

// Sets default values
ATPSSkillRangeDecalBase::ATPSSkillRangeDecalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ ���� 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RootComponent->SetMobility(EComponentMobility::Movable);

	RangeDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("RangeDecal"));

	RangeDecal->SetupAttachment(RootComponent);

	// Decal ũ�� (X�� ����, Y/Z�� ������)
	float RangeRadius = 200.f;
	RangeDecal->DecalSize = FVector(1.0f, RangeRadius, RangeRadius);

	// ȸ��: �ٴڿ� �򸮵��� Z�� ���� -90��
	RangeDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	RangeDecal->SetVisibility(true);
}
