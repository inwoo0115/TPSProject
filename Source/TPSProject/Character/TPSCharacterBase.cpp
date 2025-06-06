// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "TPSCharacterControlData.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "CharacterComponent/TPSRopeActionComponent.h"
#include "CharacterComponent/TPSWeaponComponent.h"


// Sets default values
ATPSCharacterBase::ATPSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith"));
	if (CharacterMesh.Object)
	{
		// Mesh������Ʈ�� ����
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	}

	//�����Ʈ ����
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->bEnablePhysicsInteraction = false;

	//��Ʈ��ũ ���� ����
	GetCharacterMovement()->NetworkMinTimeBetweenClientAckGoodMoves = 0.05f;
	NetUpdateFrequency = 150.f;
	MinNetUpdateFrequency = 40.0f;
	GetCharacterMovement()->NetworkSmoothingMode = ENetworkSmoothingMode::Exponential; // �Ǵ� Exponential
	GetCharacterMovement()->NetworkMaxSmoothUpdateDistance = 300.f;
	GetCharacterMovement()->NetworkNoSmoothUpdateDistance = 1000.f;

	//�̴� ���� ����
	JumpMaxCount = 2;

	//ĸ�� ������Ʈ ����
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);

	//Mesh ��ġ ����
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Character Control Manager ����
	static ConstructorHelpers::FObjectFinder<UTPSCharacterControlData> NonCombatControlDataRef(TEXT("/Game/TPSProject/CharacterControl/TPSNonCombatControl.TPSNonCombatControl"));
	if (NonCombatControlDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::NonCombat, NonCombatControlDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UTPSCharacterControlData> CombatControlDataRef(TEXT("/Game/TPSProject/CharacterControl/TPSCombatControl.TPSCombatControl"));
	if (NonCombatControlDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::Combat, CombatControlDataRef.Object);
	}

	// Camera, Spring Arm ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// RopeActionComponent ����
	RopeActionComponent = CreateDefaultSubobject<UTPSRopeActionComponent>(TEXT("RopeComponent"));

	// WeaponComponent ����
	WeaponComponent = CreateDefaultSubobject<UTPSWeaponComponent>(TEXT("WeaponComponent"));

	// Event System ����
	EventSystem = NewObject<UTPSGameplayEventSystem>();

	// ���ø����̼� ����
	bReplicates = true;
	SetReplicateMovement(true);
}

void ATPSCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// ������Ʈ �ʱ�ȭ
	WeaponComponent->Initialize(EventSystem);
}

void ATPSCharacterBase::SetCharacterControlData(ECharacterControlType ControlType)
{
	auto CharacterControlData = CharacterControlManager[ControlType];

	// Character Control Setting

	// pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	// CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;

	// SpringArm
	SpringArm->TargetArmLength = CharacterControlData->TargetArmLength;
	SpringArm->SetRelativeLocation(CharacterControlData->RelativeLocation);
	SpringArm->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	SpringArm->bInheritPitch = CharacterControlData->bInheritPitch;
	SpringArm->bInheritRoll = CharacterControlData->bInheritRoll;
	SpringArm->bInheritYaw = CharacterControlData->bInheritYaw;
	SpringArm->bDoCollisionTest = CharacterControlData->bDoCollisionTest;

	// AnimInstance
	GetMesh()->SetAnimClass(CharacterControlData->AnimBlueprintClass);

	// ���� ����
	CurrentCharacterControlType = ControlType;
}

void ATPSCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSCharacterBase, CurrentCharacterControlType);
}

void ATPSCharacterBase::OnRep_ControlType()
{
	SetCharacterControlData(CurrentCharacterControlType);
}
