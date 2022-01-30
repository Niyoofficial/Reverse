// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneManager.generated.h"

class UPaperSprite;
class UPaperSpriteComponent;

USTRUCT(BlueprintType)
struct FSpriteSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HeightOffset = 0.f;
};

USTRUCT(BlueprintType)
struct FBarricade
{
	GENERATED_BODY()

	FBarricade() {}
	FBarricade(UPaperSpriteComponent* InUpperBarricade, UPaperSpriteComponent* InDownBarricade)
		: UpperBarricade(InUpperBarricade), DownBarricade(InDownBarricade) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* UpperBarricade = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* DownBarricade = nullptr;
};

UCLASS()
class VDOWN_API ASceneManager : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* ForegroundDividerRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* ForegroundRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	class UBoxComponent* Floor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UBoxComponent* Floor2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* FirstBackgroundRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* SecondBackgroundRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* ThirdBackgroundRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* FourthBackgroundRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* UpperBarricadesRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	USceneComponent* DownBarricadesRoot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UPaperSpriteComponent* FourthUpperBackground1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UPaperSpriteComponent* FourthUpperBackground2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UPaperSpriteComponent* FourthDownBackground1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UPaperSpriteComponent* FourthDownBackground2;

public:
	ASceneManager();

	void ChangeWorld();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FSpriteSpawn GetRandomSpriteWithWeight(const TArray<FSpriteSpawn>& Array);

	void PopulateSpriteComponentArray(TArray<UPaperSpriteComponent*>& Array, int32 NumerOfComponents, USceneComponent* Parent, int32 Priority, bool bRotate);
	void InitializeSpriteComponentArray(TArray<UPaperSpriteComponent*>& BackgroundsArray, const TArray<FSpriteSpawn>& Sprites, float CellSize = -1.f,
										float SpawnChance = 1.f);
	void InitializeBarricades();
	void CheckForSpriteReplacement(TArray<UPaperSpriteComponent*>& BackgroundsArray, int32 IndexToCheck, const TArray<FSpriteSpawn>& Sprites,
								   float CellSize = -1.f, float SpawnChance = 1.f);
	void CheckForCollisionReplacement();
	void CheckForBarricadeReplacement();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Dividers)
	TArray<FSpriteSpawn> DividerSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Dividers)
	float DividerCellSize = 4096.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UpperForeground)
	TArray<FSpriteSpawn> ForegroundUpSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UpperForeground)
	float UpForegroundSpritesSpawnChance = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UpperForeground)
	float UpForegroundSpritesCellSize = 700.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UpperForeground)
	int32 MaxUpForegroundSprites = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UpperForeground)
	int32 IndexAtWhichToReplaceUpForeground = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DownForeground)
	TArray<FSpriteSpawn> ForegroundDownSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DownForeground)
	float DownForegroundSpritesSpawnChance = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DownForeground)
	float DownForegroundSpritesCellSize = 700.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DownForeground)
	int32 MaxDownForegroundSprites = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=DownForeground)
	int32 IndexAtWhichToReplaceDownForeground = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstUpperBackground)
	TArray<FSpriteSpawn> FirstUpBackgroundSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstUpperBackground)
	float FirstUpBackgroundSpritesSpawnChance = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstUpperBackground)
	float FirstUpBackgroundSpawnCellSize = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FirstUpperBackground)
	int32 FirstUpBackgroundMaxSprites = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SecondUpperBackground)
	TArray<FSpriteSpawn> SecondUpBackgroundSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SecondUpperBackground)
	float SecondUpBackgroundSpritesSpawnChance = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SecondUpperBackground)
	float SecondUpBackgroundSpawnCellSize = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SecondUpperBackground)
	int32 SecondUpBackgroundMaxSprites = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=SecondUpperBackground)
	int32 IndexAtWhichToReplaceSecondUpBackground = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ThirdUpperBackground)
	TArray<FSpriteSpawn> ThirdUpBackgroundSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ThirdUpperBackground)
	int32 NumberOfThirdUpBackgroundSprites = 6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ThirdUpperBackground)
	int32 IndexAtWhichToReplaceThirdUpBackground = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ThirdUpperBackground)
	int32 IndexAtWhichToReplaceFirstUpBackground = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FourthUpperBackground)
	TArray<FSpriteSpawn> FourthUpBackgroundSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=FourthDownBackground)
	TArray<FSpriteSpawn> FourthDownBackgroundSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=WorldTransition)
	float WorldTransitionSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Barricades)
	int32 MaxNumberOfBarricades = 6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Barricades)
	int32 IndexAtWhichToReplaceBarricade = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Barricades)
	TArray<FSpriteSpawn> UpperBarricadeSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Barricades)
	TArray<FSpriteSpawn> DownBarricadeSprites;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BarricadeOffset = 3200.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Debug)
	UPaperSprite* TestInvSprite;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<UBoxComponent*> FloorCollisions;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> UpForegrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> DownForegrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> Dividers;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> UpForegrounds2;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> FirstUpBackgrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> SecondUpBackgrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> ThirdUpBackgrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> FourthUpBackgrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<UPaperSpriteComponent*> FourthDownBackgrounds;
	UPROPERTY(VisibleAnywhere)
	TArray<FBarricade> Barricades;
	UPROPERTY()
	class AVDownCharacter* PlayerCharacter;

	TArray<float> Timings;
	int32 LastUsedTiming = 0;

	bool bUpperWorld = true;
};

