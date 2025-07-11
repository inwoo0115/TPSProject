// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment/TPSAbilityEquipmentBase.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "CharacterEquipmentAbility/TPSEquipmentAbilityBase.h"
#include "GameInstance/TPSGameplayEventSubsystem.h"
#include "Interface/TPSEventComponentInterface.h"
#include "CharacterComponent/TPSGameplayEventComponent.h"

ATPSAbilityEquipmentBase::ATPSAbilityEquipmentBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 생성 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	bReplicates = true;
	SetReplicateMovement(true);
}

void ATPSAbilityEquipmentBase::BeginPlay()
{
	Super::BeginPlay();
	
	// UI 서브시스템 캐싱
	auto GamePlayEventSystem = GetGameInstance()->GetSubsystem<UTPSGameplayEventSubsystem>();
	if (GamePlayEventSystem)
	{
		EventSystem = GamePlayEventSystem;
	}
}

void ATPSAbilityEquipmentBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason); 
	
	ClearAbilityDelegates();
}

void ATPSAbilityEquipmentBase::InitializeAbilities()
{
}

void ATPSAbilityEquipmentBase::InitializeComponent(UActorComponent* InitComponent)
{
	OwnerComponent = InitComponent;
}

void ATPSAbilityEquipmentBase::InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3)
{
	TArray<UTPSEquipmentAbilityBase*> NewSlot;

	// Ability1
	if (AbilityList.Contains(Ability1))
	{
		UTPSEquipmentAbilityBase* NewAbility1 = NewObject<UTPSEquipmentAbilityBase>(GetOwner(), AbilityList[Ability1]);
		if (NewAbility1)
		{
			NewSlot.Add(NewAbility1);
		}
	}
	// Ability2
	if (AbilityList.Contains(Ability2))
	{
		UTPSEquipmentAbilityBase* NewAbility2 = NewObject<UTPSEquipmentAbilityBase>(GetOwner(), AbilityList[Ability2]);
		if (NewAbility2)
		{
			NewSlot.Add(NewAbility2);
		}
	}
	// Ability3
	if (AbilityList.Contains(Ability3))
	{
		UTPSEquipmentAbilityBase* NewAbility3 = NewObject<UTPSEquipmentAbilityBase>(GetOwner(), AbilityList[Ability3]);
		if (NewAbility3)
		{
			NewSlot.Add(NewAbility3);
		}
	}

	AbilitySlot = NewSlot;

	// 서버일 경우 델리게이트 바인딩
	auto OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn && HasAuthority())
	{
		for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
		{
			if (Ability)
			{
				Ability->InitializeAbilityEvent();
			}
		}
	}
}

void ATPSAbilityEquipmentBase::ClearAbilityDelegates()
{
	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability)
		{
			// 델리게이트가 바인딩 되어 있을 경우 해제
			Ability->CancelAbility();
		}
	}
}

UActorComponent* ATPSAbilityEquipmentBase::GetOwnerComponent() const
{
	return OwnerComponent;
}

void ATPSAbilityEquipmentBase::ChangeFieldStatByValue(FName FieldName, float Value)
{
}


void ATPSAbilityEquipmentBase::OnRep_AbilitySlot()
{
	auto OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn && OwnerPawn->IsLocallyControlled())
	{
		for (UTPSEquipmentAbilityBase* Ability : PreviousSlot)
		{
			if (Ability)
			{
				// 델리게이트가 바인딩 되어 있을 경우 해제
				Ability->CancelAbility();
			}
		}

		for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
		{
			if (Ability)
			{
				// 델리게이트만 조정하게 변경
				Ability->InitializeAbilityEvent();
			}
		}

		// 어빌리티 변경 업데이트
		PreviousSlot = AbilitySlot;
	}
}


void ATPSAbilityEquipmentBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATPSAbilityEquipmentBase, AbilitySlot);
	DOREPLIFETIME(ATPSAbilityEquipmentBase, OwnerComponent);
}


bool ATPSAbilityEquipmentBase::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (UTPSEquipmentAbilityBase* Ability : AbilitySlot)
	{
		if (Ability)
		{
			WroteSomething |= Channel->ReplicateSubobject(Ability, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}
