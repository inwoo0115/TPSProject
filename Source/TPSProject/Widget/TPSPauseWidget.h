// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TPSPauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnQuitButtonClicked();

public:
	// 블루프린트 위젯에 있는 버튼 변수 이름과 일치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;
};
