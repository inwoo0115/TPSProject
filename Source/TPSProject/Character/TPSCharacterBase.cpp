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
#include "CharacterComponent/TPSDroneSkillComponent.h"
#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "CharacterComponent/TPSUltimateComponent.h"
#include "CharacterComponent/TPSCharacterStatComponent.h"
#include "GameInstance/TPSGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/TPSAnimMontageData.h"

// Sets default values
ATPSCharacterBase::ATPSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(TEXT("/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith"));
	if (CharacterMesh.Object)
	{
		// Mesh컴포넌트에 접근
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	}

	//무브먼트 설정
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.0f;
	GetCharacterMovement()->bEnablePhysicsInteraction = false;

	//네트워크 보정 설정
	GetCharacterMovement()->NetworkMinTimeBetweenClientAckGoodMoves = 0.05f;
	NetUpdateFrequency = 150.f;
	MinNetUpdateFrequency = 40.0f;
	GetCharacterMovement()->NetworkSmoothingMode = ENetworkSmoothingMode::Exponential; // 또는 Exponential
	GetCharacterMovement()->NetworkMaxSmoothUpdateDistance = 300.f;
	GetCharacterMovement()->NetworkNoSmoothUpdateDistance = 1000.f;

	//이단 점프 설정
	JumpMaxCount = 2;

	//캡슐 컴포넌트 설정
	GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);

	//Mesh 위치 설정
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	// AnimMontage Date 설정
	static ConstructorHelpers::FObjectFinder<UTPSAnimMontageData> AnimMontageDataRef(TEXT("/Game/TPSProject/AnimMontageData/TPSAnimMontageData.TPSAnimMontageData"));
	if (AnimMontageDataRef.Object)
	{
		AnimMontageData = AnimMontageDataRef.Object;
	}

	//Character Control Manager 설정
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

	// Camera, Spring Arm 설정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// RopeActionComponent 설정
	RopeActionComponent = CreateDefaultSubobject<UTPSRopeActionComponent>(TEXT("RopeComponent"));

	// WeaponComponent 설정
	WeaponComponent = CreateDefaultSubobject<UTPSWeaponComponent>(TEXT("WeaponComponent"));

	// StatComponent 설정
	StatComponent = CreateDefaultSubobject<UTPSCharacterStatComponent>(TEXT("StatComponent"));

	// SkillComponent 설정
	DroneComponent = CreateDefaultSubobject<UTPSDroneSkillComponent>(TEXT("DroneComponent"));
	SpAttackComponent = CreateDefaultSubobject<UTPSSpAttackSkillComponent>(TEXT("SpAttackComponent"));

	// UltimateComponent 설정
	UltimateComponent = CreateDefaultSubobject<UTPSUltimateComponent>(TEXT("UltimateComponent"));

	// 리플리케이션 설정
	bReplicates = true;
	SetReplicateMovement(true);
}

void ATPSCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Event System 설정
	EventSystem = NewObject<UTPSGameplayEventSystem>();

	// 컴포넌트 초기화
	WeaponComponent->Initialize(EventSystem);
	StatComponent->Initialize(EventSystem);
	DroneComponent->Initialize(EventSystem);
	SpAttackComponent->Initialize(EventSystem);
	UltimateComponent->Initialize(EventSystem);

	// TODO : Weapon임시 장착 (나중에 게임 인스턴스에서 한번에 불러올것)
	auto TPSGameInstance = Cast<UTPSGameInstance>(GetGameInstance());
	if (TPSGameInstance)
	{
		WeaponComponent->EquipWeapon(TPSGameInstance->WeaponClass);
	}
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

	// Input System mapping
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		// 로컬 플레이어에 해당하면 변경
		if (auto* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (auto* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				SubSystem->ClearAllMappings();
				SubSystem->AddMappingContext(CharacterControlData->InputMappingContext, 0);
			}
		}
	}

	// 현재 세팅
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
