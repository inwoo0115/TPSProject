// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "BTTask_Attack.h"
#include "Projectile/TPSProjectileBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSAIController.h"

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack");

	//ConstructorHelpers::FObjectFinder<ATPSProjectileBase> ProjectileClass(TEXT("/Game/TPSProject/Blueprints/Projectile/BP_RifleBullet.BP_RifleBullet"));
	//if (ProjectileClass.Object)
	//{
	//	DefaultProjectile = ProjectileClass.Object;
	//}
	//else
	//{
	//	DefaultProjectile = nullptr;
	//}
	ConstructorHelpers::FClassFinder<ATPSProjectileBase> ProjectileClass(TEXT("/Game/TPSProject/Blueprints/Projectile/BP_RifleBullet.BP_RifleBullet_C"));
	if (ProjectileClass.Succeeded())
	{
		DefaultProjectile = ProjectileClass.Class;
	}
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (nullptr == TargetPawn)
	{
		return EBTNodeResult::Failed;
	}

	FName SocketName = TEXT("Muzzle_01");
	FVector StartLocation;
	if (USkeletalMeshComponent* MeshComp = ControllingPawn->FindComponentByClass<USkeletalMeshComponent>())
	{
		StartLocation = MeshComp->GetSocketLocation(SocketName);
	}
	else
	{
		StartLocation = ControllingPawn->GetActorLocation();
	}



	// �ѱ� ��ġ���� Ÿ�� ���� ���
	FVector MuzzleLocation = StartLocation + ControllingPawn->GetActorForwardVector() * 50.0f;
	FVector ShotDirection = (TargetPawn->GetActorLocation() - MuzzleLocation).GetSafeNormal();
	FRotator ShotRotation = ShotDirection.Rotation();

	// �Ѿ� ����
	FActorSpawnParameters SpawnParams;

	SpawnParams.Owner = ControllingPawn;
	SpawnParams.Instigator = ControllingPawn;

	// �Ѿ� Ŭ���� ����
	auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
		DefaultProjectile,
		MuzzleLocation,
		ShotRotation,
		SpawnParams
	);

	// �Ѿ� ����ü�� ��������� ���� ����
	if (Projectile)
	{
		Projectile->Damage = 10.0f;
		return EBTNodeResult::Succeeded;
		UE_LOG(LogTemp, Warning, TEXT("Projectile Spawned Successfully!"));
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
