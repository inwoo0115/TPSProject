// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "Animation/TPSAnimMontageData.h"
#include "Player/TPSPlayerController.h"	
#include "Interface/TPSInteractableInterface.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interaction/TPSSpInteractionObjectBase.h"
#include "CharacterComponent/TPSRopeActionComponent.h"
#include "CharacterComponent/TPSWeaponComponent.h"
#include "CharacterComponent/TPSDroneSkillComponent.h"
#include "CharacterComponent/TPSSpAttackSkillComponent.h"
#include "CharacterComponent/TPSUltimateComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"





ATPSCharacterPlayer::ATPSCharacterPlayer()
{
	//Input 설정
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Move.IA_Move"));
	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AimActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Aim.IA_Aim"));
	if (AimActionRef.Object)
	{
		AimAction = AimActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Attack.IA_Attack"));
	if (AttackActionRef.Object)
	{
		AttackAction = AttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> DroneActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Drone.IA_Drone"));
	if (DroneActionRef.Object)
	{
		DroneAction = DroneActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> EscActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Esc.IA_Esc"));
	if (EscActionRef.Object)
	{
		EscAction = EscActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InfoActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Info.IA_Info"));
	if (InfoActionRef.Object)
	{
		InfoAction = InfoActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InteractActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Interact.IA_Interact"));
	if (InteractActionRef.Object)
	{
		InteractAction = InteractActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Jump.IA_Jump"));
	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Look.IA_Look"));
	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ReloadActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Reload.IA_Reload"));
	if (ReloadActionRef.Object)
	{
		ReloadAction = ReloadActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> RunActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Run.IA_Run"));
	if (RunActionRef.Object)
	{
		RunAction = RunActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SpActionActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_SpAction.IA_SpAction"));
	if (SpActionActionRef.Object)
	{
		SpActionAction = SpActionActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SpAttackActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_SpAttack.IA_SpAttack"));
	if (SpAttackActionRef.Object)
	{
		SpAttackAction = SpAttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> UltimateActionRef(TEXT("/Game/TPSProject/Input/Actions/IA_Ultimate.IA_Ultimate"));
	if (UltimateActionRef.Object)
	{
		UltimateAction = UltimateActionRef.Object;
	}
}

void ATPSCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	// 컨트롤 데이터 기반 초기화
	SetCharacterControlData(CurrentCharacterControlType);

	// AimTimeline 초기화
	AimCurveFloat = NewObject<UCurveFloat>(this, TEXT("AimCurveFloat"));
	FRichCurve& RichCurve = AimCurveFloat->FloatCurve;
	RichCurve.AddKey(0.0f, 300.0f); // 시작 시점
	RichCurve.AddKey(0.1f, 40.0f); // 끝 시점
	OnTimelineFloatCallback.BindUFunction(this, FName("AimUpdate"));
	AimTimeline.AddInterpFloat(AimCurveFloat, OnTimelineFloatCallback);
	AimTimeline.SetLooping(false);
	AimTimeline.SetPlayRate(1.0f);
}

void ATPSCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Binding
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATPSCharacterPlayer::Jump);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ATPSCharacterPlayer::Run);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Attack);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::AimIn);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ATPSCharacterPlayer::AimOut);
	EnhancedInputComponent->BindAction(SpActionAction, ETriggerEvent::Completed, this, &ATPSCharacterPlayer::SpAction);
	EnhancedInputComponent->BindAction(SpAttackAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::SpAttack);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Reload);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Interact);
	EnhancedInputComponent->BindAction(UltimateAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Ultimate);
	EnhancedInputComponent->BindAction(DroneAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Drone);
	EnhancedInputComponent->BindAction(InfoAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Info);
	EnhancedInputComponent->BindAction(EscAction, ETriggerEvent::Completed, this, &ATPSCharacterPlayer::Esc);
}

void ATPSCharacterPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 특수 상호작용 오브젝트가 있는지 확인
	CheckSpInteraction();

	// Timeline 업데이트
	AimTimeline.TickTimeline(DeltaSeconds);
}

void ATPSCharacterPlayer::CheckSpInteraction()
{
	// 상호작용 가능한 오브젝트가 있을 경우 서버에서 업데이트
	if (HasAuthority())
	{
		// SpInteraction Object가 있는 지 확인하기 위한 Profile Trace
		FVector3d StartLocation = GetActorLocation();
		FVector3d DirectionVector = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
		FHitResult HitResult;
		bool bHit = GetWorld()->SweepSingleByProfile(
			HitResult,
			StartLocation + DirectionVector * 50,
			StartLocation + DirectionVector * 2500,
			FQuat::Identity,
			TEXT("InteractionProfile"),
			FCollisionShape::MakeSphere(200.0f)
		);

		if (bHit)
		{
			auto* SpInteractionObject = Cast<ATPSSpInteractionObjectBase>(HitResult.GetActor());
			if (SpInteractionObject)
			{
				SpInteractionTargetActor = SpInteractionObject;
			}
		}

		else
		{
			if (SpInteractionTargetActor)
			{
				SpInteractionTargetActor = nullptr;
			}
		}
	}

	if (IsLocallyControlled())
	{
		if (SpInteractionTargetActor)
		{
			// object가 있을 경우 UI 띄우기
			SpInteractionTargetActor->TraceBeginOverlap(GetController());
		}
		else
		{
			// 없을 경우 UI 제거
			SpInteractionTargetActor->TraceEndOverlap(GetController());
		}
	}
}


void ATPSCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	// 컨트롤러 회전 값
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// 방향 구하기.
	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 무브먼트 컴포넌트에 값 전달.
	AddMovementInput(ForwardVector, Movement.X);
	AddMovementInput(RightVector, Movement.Y);
}

void ATPSCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	// 시점 회전
	AddControllerPitchInput(Movement.Y * -1);
	AddControllerYawInput(Movement.X);
}

void ATPSCharacterPlayer::Jump()
{
	if (IsLocallyControlled())
	{
		Super::Jump();
	}
}

void ATPSCharacterPlayer::Run(const FInputActionValue& Value)
{
	if (IsLocallyControlled())
	{
		ServerRPCRunAction();
	}
}

void ATPSCharacterPlayer::Attack(const FInputActionValue& Value)
{
	if (IsLocallyControlled() && WeaponComponent->GetCanLaunchWeapon())
	{
		WeaponComponent->LaunchWeapon();
		// 로컬에서 공격
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::Attack]);

		// 로컬 클라이언트일 경우 서버 RPC 전송
		if (!HasAuthority())
		{
			ServerRPCAttackAction();
		}
		else
		{
			MulticastRPCAttackAction();
		}
	}
}

void ATPSCharacterPlayer::AimIn(const FInputActionValue& Value)
{
	if (AimCurveFloat)
	{
		AimTimeline.Play(); // Timeline 시작
	}
	IsAim = true;
}

void ATPSCharacterPlayer::AimOut(const FInputActionValue& Value)
{
	if (AimCurveFloat)
	{
		AimTimeline.Reverse(); // Timeline 역재생
	}
	IsAim = false;
}

void ATPSCharacterPlayer::SpAction(const FInputActionValue& Value)
{
	if (IsLocallyControlled() && !HasAuthority())
	{
		ServerRPCSpAction();
	}

	// 오차 보정을 위해 클라이언트도 같이 계산 + 호스트 클라이언트 실행
	if (RopeActionComponent->GetIsGrappling())
	{
		// RopeActionComponent 설정
		RopeActionComponent->SetIsGrappling(false);
		RopeActionComponent->UnregisterComponent();
	}
	else if (SpInteractionTargetActor)
	{
		//애님 몽타주 재생
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::RopeAction]);

		// RopeActionComponent 설정
		RopeActionComponent->SetIsGrappling(true);
		RopeActionComponent->SetRopeLocation(SpInteractionTargetActor->GetActorLocation());
		// 물체와 플레이어 잇는 케이블 활성화
		RopeActionComponent->RegisterComponent();
		RopeActionComponent->SetAttachEndTo(SpInteractionTargetActor, TEXT("StaticMesh"));
	}
}

void ATPSCharacterPlayer::SpAttack(const FInputActionValue& Value)
{
	if (IsLocallyControlled())
	{
		// Server RPC
		// MultiCast로 애님 몽타주 재생
	}
}

void ATPSCharacterPlayer::Interact(const FInputActionValue& Value)
{
	if (IsLocallyControlled())
	{
		auto PC = Cast<ATPSPlayerController>(GetController());
		if (PC)
		{
			for (auto& Elem : PC->InteractionUIManager)
			{
				if (Elem.Value.bCanInteract)
				{
					auto Interactable = Cast<ITPSInteractableInterface>(Elem.Value.TargetActor);
					if (Interactable)
					{
						Interactable->Interact(PC);
					}
				}
			}
		}
	}
}

void ATPSCharacterPlayer::Drone(const FInputActionValue& Value)
{
}

void ATPSCharacterPlayer::Reload(const FInputActionValue& Value)
{
	if (IsLocallyControlled() && WeaponComponent->GetCanReloadWeapon())
	{
		//애님 몽타주 재생
		WeaponComponent->ReloadWeapon();
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::Reload]);
	}
}

void ATPSCharacterPlayer::Ultimate(const FInputActionValue& Value)
{
}

void ATPSCharacterPlayer::Esc(const FInputActionValue& Value)
{
	if (IsLocallyControlled())
	{
		auto UISubsystem = GetGameInstance()->GetSubsystem<UTPSUiSubsystem>();
		if (UISubsystem)
		{
			if (UISubsystem->GetCurrentUI() == EUIType::None)
			{
				UISubsystem->ShowUI(EUIType::Pause);
			}
			// TODO: 일단 ui키면 입력을 받지 않아서 의미가 없음 수정 예정
			//else
			//{
			//	UISubsystem->HideCurrentUI();
			//}
		}
	}
}

void ATPSCharacterPlayer::Info(const FInputActionValue& Value)
{
	// Character 정보 UI 띄우기
}

void ATPSCharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSCharacterPlayer, SpInteractionTargetActor);
	DOREPLIFETIME(ATPSCharacterPlayer, IsRun);
}

void ATPSCharacterPlayer::ServerRPCSpAction_Implementation()
{
	if (RopeActionComponent->GetIsGrappling())
	{
		// RopeActionComponent 설정
		RopeActionComponent->SetIsGrappling(false);
		RopeActionComponent->UnregisterComponent();
	}
	else if (SpInteractionTargetActor)
	{

		// RopeActionComponent 설정
		RopeActionComponent->SetIsGrappling(true);
		RopeActionComponent->SetRopeLocation(SpInteractionTargetActor->GetActorLocation());
		// 물체와 플레이어 잇는 케이블 활성화
		RopeActionComponent->RegisterComponent();
		RopeActionComponent->SetAttachEndTo(SpInteractionTargetActor, TEXT("StaticMesh"));
	}
}

void ATPSCharacterPlayer::ServerRPCRunAction_Implementation()
{
	if (IsRun)
	{
		IsRun = false;
		GetCharacterMovement()->MaxWalkSpeed -= 300.0f;
	}
	else
	{
		IsRun = true;
		GetCharacterMovement()->MaxWalkSpeed += 300.0f;

	}
}

void ATPSCharacterPlayer::ServerRPCAttackAction_Implementation()
{
	MulticastRPCAttackAction();

	if (!IsLocallyControlled())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::Attack]);
	}
}

void ATPSCharacterPlayer::MulticastRPCAttackAction_Implementation()
{
	// 컨트롤 하지 않는 클라이언트 몽타주 재생
	if (!IsLocallyControlled())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::Attack]);
	}
}

void ATPSCharacterPlayer::OnRepIsRun()
{
	if (IsRun)
	{
		GetCharacterMovement()->MaxWalkSpeed += 300.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed -= 300.0f;
	}
}

void ATPSCharacterPlayer::AimUpdate(float Value)
{
	// Timeline에서 설정한 값으로 카메라 거리 조정
	SpringArm->TargetArmLength = Value; 
}

void ATPSCharacterPlayer::StartAttack()
{
	WeaponComponent->FireWeapon();
	if (IsLocallyControlled())
	{
		WeaponComponent->EffectWeapon();
	}
}

void ATPSCharacterPlayer::StartSpAttack()
{
	//SpAttackComponent->CastSkill();
}
