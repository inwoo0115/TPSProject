// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSServerJoinButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSServerJoinButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnJoinButtonClicked();

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerNameText;

	int32 SessionIndex;
};
