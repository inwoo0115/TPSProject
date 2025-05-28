// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/TPSLoadingWidget.h"
#include "Components/ProgressBar.h"

void UTPSLoadingWidget::UpdateProgress(float Value)
{
	if (LoadingProgressBar)
		LoadingProgressBar->SetPercent(Value);
}
