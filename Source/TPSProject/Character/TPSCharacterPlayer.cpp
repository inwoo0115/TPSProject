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
	//Input ����
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

	// ��Ʈ�� ������ ��� �ʱ�ȭ
	SetCharacterControlData(CurrentCharacterControlType);

	// AimTimeline �ʱ�ȭ
	AimCurveFloat = NewObject<UCurveFloat>(this, TEXT("AimCurveFloat"));
	FRichCurve& RichCurve = AimCurveFloat->FloatCurve;
	RichCurve.AddKey(0.0f, 300.0f); // ���� ����
	RichCurve.AddKey(0.1f, 40.0f); // �� ����
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

	// Ư�� ��ȣ�ۿ� ������Ʈ�� �ִ��� Ȯ��
	CheckSpInteraction();

	// Timeline ������Ʈ
	AimTimeline.TickTimeline(DeltaSeconds);
}

void ATPSCharacterPlayer::CheckSpInteraction()
{
	// ��ȣ�ۿ� ������ ������Ʈ�� ���� ��� �������� ������Ʈ
	if (HasAuthority())
	{
		// SpInteraction Object�� �ִ� �� Ȯ���ϱ� ���� Profile Trace
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
			// object�� ���� ��� UI ����
			SpInteractionTargetActor->TraceBeginOverlap(GetController());
		}
		else
		{
			// ���� ��� UI ����
			SpInteractionTargetActor->TraceEndOverlap(GetController());
		}
	}
}


void ATPSCharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	// ��Ʈ�ѷ� ȸ�� ��
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// ���� ���ϱ�.
	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// �����Ʈ ������Ʈ�� �� ����.
	AddMovementInput(ForwardVector, Movement.X);
	AddMovementInput(RightVector, Movement.Y);
}

void ATPSCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	// ���� ȸ��
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
		// ���ÿ��� ����
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::Attack]);

		// ���� Ŭ���̾�Ʈ�� ��� ���� RPC ����
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
		AimTimeline.Play(); // Timeline ����
	}
	IsAim = true;
}

void ATPSCharacterPlayer::AimOut(const FInputActionValue& Value)
{
	if (AimCurveFloat)
	{
		AimTimeline.Reverse(); // Timeline �����
	}
	IsAim = false;
}

void ATPSCharacterPlayer::SpAction(const FInputActionValue& Value)
{
	if (IsLocallyControlled() && !HasAuthority())
	{
		ServerRPCSpAction();
	}

	// ���� ������ ���� Ŭ���̾�Ʈ�� ���� ��� + ȣ��Ʈ Ŭ���̾�Ʈ ����
	if (RopeActionComponent->GetIsGrappling())
	{
		// RopeActionComponent ����
		RopeActionComponent->SetIsGrappling(false);
		RopeActionComponent->UnregisterComponent();
	}
	else if (SpInteractionTargetActor)
	{
		//�ִ� ��Ÿ�� ���
		GetMesh()->GetAnimInstance()->Montage_Play(AnimMontageData->AnimMontages[EMontageType::RopeAction]);

		// RopeActionComponent ����
		RopeActionComponent->SetIsGrappling(true);
		RopeActionComponent->SetRopeLocation(SpInteractionTargetActor->GetActorLocation());
		// ��ü�� �÷��̾� �մ� ���̺� Ȱ��ȭ
		RopeActionComponent->RegisterComponent();
		RopeActionComponent->SetAttachEndTo(SpInteractionTargetActor, TEXT("StaticMesh"));
	}
}

void ATPSCharacterPlayer::SpAttack(const FInputActionValue& Value)
{
	if (IsLocallyControlled())
	{
		// Server RPC
		// MultiCast�� �ִ� ��Ÿ�� ���
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
		//�ִ� ��Ÿ�� ���
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
			// TODO: �ϴ� uiŰ�� �Է��� ���� �ʾƼ� �ǹ̰� ���� ���� ����
			//else
			//{
			//	UISubsystem->HideCurrentUI();
			//}
		}
	}
}

void ATPSCharacterPlayer::Info(const FInputActionValue& Value)
{
	// Character ���� UI ����
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
		// RopeActionComponent ����
		RopeActionComponent->SetIsGrappling(false);
		RopeActionComponent->UnregisterComponent();
	}
	else if (SpInteractionTargetActor)
	{

		// RopeActionComponent ����
		RopeActionComponent->SetIsGrappling(true);
		RopeActionComponent->SetRopeLocation(SpInteractionTargetActor->GetActorLocation());
		// ��ü�� �÷��̾� �մ� ���̺� Ȱ��ȭ
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
	// ��Ʈ�� ���� �ʴ� Ŭ���̾�Ʈ ��Ÿ�� ���
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
	// Timeline���� ������ ������ ī�޶� �Ÿ� ����
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
