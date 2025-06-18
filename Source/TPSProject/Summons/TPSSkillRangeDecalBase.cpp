// Fill out your copyright notice in the Description page of Project Settings.


#include "Summons/TPSSkillRangeDecalBase.h"
#include "Components/DecalComponent.h"

// Sets default values
ATPSSkillRangeDecalBase::ATPSSkillRangeDecalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 생성 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	RootComponent->SetMobility(EComponentMobility::Movable);

	RangeDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("RangeDecal"));

	RangeDecal->SetupAttachment(RootComponent);

	// Decal 크기 (X는 높이, Y/Z는 반지름)
	float RangeRadius = 200.f;
	RangeDecal->DecalSize = FVector(1.0f, RangeRadius, RangeRadius);

	// 회전: 바닥에 깔리도록 Z축 기준 -90도
	RangeDecal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	RangeDecal->SetVisibility(true);
}
