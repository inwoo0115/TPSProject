// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemInfoText;

protected:
	virtual void NativeConstruct() override;
};
