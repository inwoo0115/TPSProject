// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSCharacterPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Player/TPSPlayerController.h"	
#include "Interface/TPSInteractableInterface.h"
#include "GameInstance/TPSUiSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interaction/TPSSpInteractionObjectBase.h"
#include "CharacterComponent/TPSRopeActionComponent.h"
#include "Net/UnrealNetwork.h"

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

	// Input Mapping Context ��������
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/TPSProject/Input/IMC_TPSCharacter.IMC_TPSCharacter'"));
	if (IMCRef.Object)
	{
		InputMappingContext = IMCRef.Object;
	}
}

void ATPSCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Input system mapping
	if (IsLocallyControlled())
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			if (auto* LocalPlayer = PlayerController->GetLocalPlayer())
			{
				if (auto* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
				{
					SubSystem->AddMappingContext(InputMappingContext, 0);
				}
			}
		}
	}
	SetCharacterControlData(CurrentCharacterControlType);
}

void ATPSCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Binding
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Jump);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATPSCharacterPlayer::MoveComplete);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ATPSCharacterPlayer::Run);
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

void ATPSCharacterPlayer::Tick(float DeltaSecounds)
{
	Super::Tick(DeltaSecounds);

	CheckSpInteraction();
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

void ATPSCharacterPlayer::MoveComplete(const FInputActionValue& Value)
{
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
		if (IsRun)
		{
			IsRun = false;
			GetCharacterMovement()->MaxWalkSpeed -= 300.0;
		}
		else
		{
			IsRun = true;
			GetCharacterMovement()->MaxWalkSpeed += 300.0;
		}
	}
}

void ATPSCharacterPlayer::Attack(const FInputActionValue& Value)
{
}

void ATPSCharacterPlayer::AimIn(const FInputActionValue& Value)
{
}

void ATPSCharacterPlayer::AimOut(const FInputActionValue& Value)
{
}

void ATPSCharacterPlayer::SpAction(const FInputActionValue& Value)
{
	if (IsLocallyControlled() && !HasAuthority())
	{
		ServerRPCSpAction();
	}

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

void ATPSCharacterPlayer::SpAttack(const FInputActionValue& Value)
{
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
}

void ATPSCharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSCharacterPlayer, SpInteractionTargetActor);
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
