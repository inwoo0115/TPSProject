// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TPSPreviewCharacter.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

ATPSPreviewCharacter::ATPSPreviewCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SceneCaptureComponent ����
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
	SceneCapture->SetupAttachment(RootComponent);

	SceneCapture->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth; // �Ǵ� SCS_FinalColorLDR
	SceneCapture->CompositeMode = SCCM_Overwrite;
	SceneCapture->bCaptureEveryFrame = true;
	SceneCapture->bCaptureOnMovement = false;
	SceneCapture->ShowFlags.SetAtmosphere(false); 
	SceneCapture->ShowFlags.SetFog(false); 
	SceneCapture->ShowFlags.SetStaticMeshes(false);

	// ĸó ǰ�� �ɼ� ���� (������)
	SceneCapture->bCaptureEveryFrame = true;
	SceneCapture->bCaptureOnMovement = false;

	// Render Target ����
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderTargetRef(TEXT("/Game/TPSProject/Texture/RT_PlayerPreview.RT_PlayerPreview"));
	if (RenderTargetRef.Object)
	{
		SceneCapture->TextureTarget = RenderTargetRef.Object;
	}
}
