// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSPreviewCharacter.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPreviewCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSPreviewCharacter();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USceneCaptureComponent2D> SceneCapture;

};
