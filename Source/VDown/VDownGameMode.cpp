// Copyright Epic Games, Inc. All Rights Reserved.


#include "VDownGameMode.h"

#include "SceneManager.h"
#include "VDownCharacter.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"


AVDownGameMode::AVDownGameMode()
{
	Bright = CreateDefaultSubobject<UAudioComponent>("Bright");
	Bright->SetupAttachment(RootComponent);

	Dark = CreateDefaultSubobject<UAudioComponent>("Dark");
	Dark->SetupAttachment(RootComponent);
}

void AVDownGameMode::SetWorld(bool bUpper)
{
	if (bUpper)
	{
		Bright->SetLowPassFilterFrequency(20000.f);
		Bright->SetLowPassFilterEnabled(false);
		Bright->SetVolumeMultiplier(1.f);
		Dark->SetLowPassFilterEnabled(true);
		Dark->SetLowPassFilterFrequency(LowPass);
		Dark->SetVolumeMultiplier(Volume);
	}
	else
	{
		Dark->SetLowPassFilterFrequency(20000.f);
		Dark->SetLowPassFilterEnabled(false);
		Dark->SetVolumeMultiplier(1.f);
		Bright->SetLowPassFilterEnabled(true);
		Bright->SetLowPassFilterFrequency(LowPass);
		Bright->SetVolumeMultiplier(Volume);
	}
}

void AVDownGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetWorld(true);

	PlayerCharacter = CastChecked<AVDownCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	SceneManager = GetWorld()->SpawnActor<ASceneManager>(SceneManagerClass);
}
