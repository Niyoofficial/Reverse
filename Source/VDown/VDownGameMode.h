// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VDownGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VDOWN_API AVDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UAudioComponent* Bright;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	UAudioComponent* Dark;

public:
	AVDownGameMode();

	void SetWorld(bool bUpper);

	class ASceneManager* GetSceneManager() const { return SceneManager; }
	class AVDownCharacter* GetVDownCharacter() const { return PlayerCharacter; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ASceneManager> SceneManagerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float LowPass = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Volume = 0.5f;

private:
	UPROPERTY()
	ASceneManager* SceneManager;

	UPROPERTY()
	AVDownCharacter* PlayerCharacter;
};
