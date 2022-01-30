// Fill out your copyright notice in the Description page of Project Settings.


#include "VDownHelpers.h"

#include "VDownGameMode.h"

AVDownGameMode* UVDownHelpers::GetVDownGameMode(const UObject* Context)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(Context, EGetWorldErrorMode::Assert);
	return CastChecked<AVDownGameMode>(World->GetAuthGameMode());
}
