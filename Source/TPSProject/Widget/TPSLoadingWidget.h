// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSLoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSLoadingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* LoadingProgressBar;

	void UpdateProgress(float Value);
};
