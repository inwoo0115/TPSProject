// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentAbility/TPSAbilityType.h"
#include "Projectile/TPSProjectileType.h"
#include "CharacterComponent/TPSGameplayEventSystem.h"
#include "TPSWeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FWeaponContext
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UltiGaugeRatio = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequireAmmo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EProjectileType CurrentBullet = EProjectileType::RifleBullet;
};


UCLASS()
class TPSPROJECT_API ATPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	ATPSWeaponBase();

	// ���� ��� ���� �Լ� 
	virtual void Launch();

	virtual void Fire();

	virtual void Release();

	virtual void Reload();

	virtual void Effect();

	// Getter
	bool CanReload();

	bool CanFire();

	// ���� ���� �ʱ�ȭ
	void SetWeaponContextFromData();

	// ������Ʈ�� Ư�� ����
	void InitializeAbilities();

	// ���� ������ ����
	void InitializeComponent(UActorComponent* InitComponent);

	// ������ ���¿��� Ư�� �ʱ�ȭ
	void InitializeAbilitiesFromDataAsset(EAbilityType Ability1, EAbilityType Ability2, EAbilityType Ability3);

	// ��밡���� ��ü Ư�� �迭
	UPROPERTY(ReplicatedUsing = OnRep_AbilitySlot)
	TArray<class UTPSEquipmentAbilityBase*> AbilitySlot;

	// Ư�� �迭 ��ȭ �� ����
	UFUNCTION()
	void OnRep_AbilitySlot();

	// ���� ���� ������ ����
	UPROPERTY(Replicated)
	TObjectPtr<class UTPSWeaponData> WeaponData;

	UPROPERTY(Replicated)
	bool bCanFire = true;

	UPROPERTY(Replicated)
	bool bIsReloading = false;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	UActorComponent* GetOwnerComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FWeaponContext GetWeaponContext() const;

	// ���� Ư�� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EProjectileType, TSubclassOf<class ATPSProjectileBase>> ProjectileList;

	// ���� �߻�ü Ŭ���� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EAbilityType, TSubclassOf<class UTPSEquipmentAbilityBase>> AbilityList;

protected:
	// ��� ������ Ÿ�̸�
	FTimerHandle FireCooldownHandle;

	// RPC
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// ���� ������Ʈ
	UPROPERTY(Replicated)
	TObjectPtr<class UActorComponent> OwnerComponent;

	// ���� ���� ����ü
	UPROPERTY(Replicated, BlueprintReadOnly)
	FWeaponContext WeaponContext;

	// ���� ���ø����̼�
	bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags);
};
