// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "BTTask_Attack.h"
#include "Projectile/TPSProjectileBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TPSAIController.h"
#include "Math/UnrealMathUtility.h"

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack");

	ConstructorHelpers::FClassFinder<ATPSProjectileBase> ProjectileClass(TEXT("/Game/TPSProject/Blueprints/Projectile/BP_RifleBullet.BP_RifleBullet_C"));
	if (ProjectileClass.Succeeded())
	{
		DefaultProjectile = ProjectileClass.Class;
	}

	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AttackCoolTime = 0.0f;

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AttackCoolTime += DeltaSeconds;
	if (AttackCoolTime > 0.2f)
	{
		Fire(OwnerComp, NodeMemory, DeltaSeconds);
		AttackCoolTime = 0.0f;
	}
}

void UBTTask_Attack::Fire(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	APawn* TargetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (nullptr == TargetPawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
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
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// ���Ժ��� ��� ���� ����
	float HalfAngleRad = FMath::DegreesToRadians(5.0f);
	FVector RandomDir = FMath::VRandCone(ShotDirection, HalfAngleRad, HalfAngleRad);

	// �Ѿ� Ŭ���� ����
	auto Projectile = GetWorld()->SpawnActor<ATPSProjectileBase>(
		DefaultProjectile,
		MuzzleLocation,
		RandomDir.Rotation(),
		SpawnParams
	);

	// �Ѿ� ����ü�� ��������� ���� ����
	if (Projectile)
	{
		Projectile->Damage = 10.0f;
		UE_LOG(LogTemp, Warning, TEXT("Projectile spawned"));
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile spawn failed"));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}