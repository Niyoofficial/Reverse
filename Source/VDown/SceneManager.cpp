// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneManager.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "VDownCharacter.h"
#include "VDownGameMode.h"
#include "Components/BoxComponent.h"


ASceneManager::ASceneManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	ForegroundDividerRoot = CreateDefaultSubobject<USceneComponent>("ForegroundDividerRoot");
	ForegroundDividerRoot->SetupAttachment(Root);

	ForegroundRoot = CreateDefaultSubobject<USceneComponent>("ForegroundRoot");
	ForegroundRoot->SetupAttachment(Root);

	Floor = CreateDefaultSubobject<UBoxComponent>("Floor");
	Floor->SetupAttachment(Root);
	Floor->SetBoxExtent(FVector(5000.f, 30.f, 5.f));
	Floor->SetAbsolute(false, true);

	Floor2 = CreateDefaultSubobject<UBoxComponent>("Floor2");
	Floor2->SetupAttachment(Root);
	Floor2->SetBoxExtent(FVector(5000.f, 30.f, 5.f));
	Floor2->SetRelativeLocation(FVector(10000.f, 0.f, 0.f));
	Floor2->SetAbsolute(false, true);

	FirstBackgroundRoot = CreateDefaultSubobject<USceneComponent>("FirstBackgroundRoot");
	FirstBackgroundRoot->SetupAttachment(Root);

	SecondBackgroundRoot = CreateDefaultSubobject<USceneComponent>("SecondBackgroundRoot");
	SecondBackgroundRoot->SetupAttachment(Root);

	ThirdBackgroundRoot = CreateDefaultSubobject<USceneComponent>("ThirdBackgroundRoot");
	ThirdBackgroundRoot->SetupAttachment(Root);

	FourthBackgroundRoot = CreateDefaultSubobject<USceneComponent>("FourthBackgroundRoot");
	FourthBackgroundRoot->SetupAttachment(Root);

	FourthUpperBackground1 = CreateDefaultSubobject<UPaperSpriteComponent>("FourthUpperBackground1");
	FourthUpperBackground1->SetupAttachment(FourthBackgroundRoot);

	FourthUpperBackground2 = CreateDefaultSubobject<UPaperSpriteComponent>("FourthUpperBackground2");
	FourthUpperBackground2->SetupAttachment(FourthBackgroundRoot);

	FourthDownBackground1 = CreateDefaultSubobject<UPaperSpriteComponent>("FourthDownBackground1");
	FourthDownBackground1->SetupAttachment(FourthBackgroundRoot);

	FourthDownBackground2 = CreateDefaultSubobject<UPaperSpriteComponent>("FourthDownBackground2");
	FourthDownBackground2->SetupAttachment(FourthBackgroundRoot);
	FourthDownBackground2->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));

	UpperBarricadesRoot = CreateDefaultSubobject<USceneComponent>("UpperBarricadesRoot");
	UpperBarricadesRoot->SetupAttachment(Root);

	DownBarricadesRoot = CreateDefaultSubobject<USceneComponent>("DownBarricadesRoot");
	DownBarricadesRoot->SetupAttachment(Root);

	Timings =
	{
		7.111,
		8.000,
		8.888,
		10.666,
		11.555,
		12.444,
		14.222,
		15.111,
		16.000,
		16.888,
		17.777,
		18.666,
		19.555,
		20.888,
		21.333,
		22.222,
		23.111,
		24.888,
		25.777,
		26.666,
		28.000,
		28.444,
		29.333,
		30.222,
		31.111,
		31.555,
		32.000,
		32.888,
		33.777,
		35.111,
		36.000,
		36.888,
		37.777,
		38.666,
		39.555,
		40.444,
		41.333,
		42.222,
		43.111,
		44.000,
		44.888,
		45.777,
		46.666,
		47.555,
		48.444,
		49.333,
		49.777,
		50.666,
		51.555,
		52.444,
		53.333,
		54.222,
		55.111,
		56.000,
		56.888,
		57.777,
		58.666,
		59.555,
		60.444,
		61.333,
		62.222,
		63.111,
		64.000,
		64.444,
		64.888,
		65.777,
		66.666,
		67.555,
		68.000,
		68.444,
		68.888,
		69.777,
		70.666,
		71.111,
		72.000,
		72.888,
		74.777,
		75.666,
		76.500,
		77.950,
		79.111,
		80.000,
		81.777,
		82.666,
		83.555,
		84.000,
		85.333,
		86.250,
		86.666,
		87.111,
		88.888,
		89.333,
		90.222,
		90.666,
		92.000
	};
}

void ASceneManager::ChangeWorld()
{
	bUpperWorld = !bUpperWorld;
	UVDownHelpers::GetVDownGameMode(this)->SetWorld(bUpperWorld);
}

void ASceneManager::BeginPlay()
{
	Super::BeginPlay();

	FloorCollisions.Emplace(Floor);
	FloorCollisions.Emplace(Floor2);

	PlayerCharacter = UVDownHelpers::GetVDownGameMode(this)->GetVDownCharacter();

	FourthUpBackgrounds.Emplace(FourthUpperBackground1);
	FourthUpBackgrounds.Emplace(FourthUpperBackground2);

	InitializeSpriteComponentArray(FourthUpBackgrounds, FourthUpBackgroundSprites);

	PopulateSpriteComponentArray(ThirdUpBackgrounds, NumberOfThirdUpBackgroundSprites, ThirdBackgroundRoot, 0, false);
	InitializeSpriteComponentArray(ThirdUpBackgrounds, ThirdUpBackgroundSprites);

	PopulateSpriteComponentArray(FirstUpBackgrounds, FirstUpBackgroundMaxSprites, FirstBackgroundRoot, 2, false);
	InitializeSpriteComponentArray(FirstUpBackgrounds, FirstUpBackgroundSprites, FirstUpBackgroundSpawnCellSize, FirstUpBackgroundSpritesSpawnChance);

	PopulateSpriteComponentArray(SecondUpBackgrounds, SecondUpBackgroundMaxSprites, SecondBackgroundRoot, 1, false);
	InitializeSpriteComponentArray(SecondUpBackgrounds, SecondUpBackgroundSprites, SecondUpBackgroundSpawnCellSize,
								   SecondUpBackgroundSpritesSpawnChance);

	PopulateSpriteComponentArray(UpForegrounds, MaxUpForegroundSprites, ForegroundRoot, 6, false);
	InitializeSpriteComponentArray(UpForegrounds, ForegroundUpSprites, UpForegroundSpritesCellSize, UpForegroundSpritesSpawnChance);

	PopulateSpriteComponentArray(Dividers, 3, ForegroundDividerRoot, 5, false);
	InitializeSpriteComponentArray(Dividers, DividerSprites, DividerCellSize);

	FourthDownBackgrounds.Emplace(FourthDownBackground1);
	FourthDownBackgrounds.Emplace(FourthDownBackground2);

	InitializeSpriteComponentArray(FourthDownBackgrounds, FourthDownBackgroundSprites);

	PopulateSpriteComponentArray(DownForegrounds, MaxDownForegroundSprites, ForegroundRoot, 3, true);
	InitializeSpriteComponentArray(DownForegrounds, ForegroundDownSprites, DownForegroundSpritesCellSize, DownForegroundSpritesSpawnChance);

	InitializeBarricades();

	FTimerHandle Temp;
	GetWorldTimerManager().SetTimer(Temp, [this]()
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), PlayerCharacter->GetActorLocation().X);
	}, 1.f, true);
}

void ASceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckForSpriteReplacement(FourthUpBackgrounds, 1, FourthUpBackgroundSprites);
	CheckForSpriteReplacement(FourthDownBackgrounds, 1, FourthDownBackgroundSprites);
	CheckForSpriteReplacement(ThirdUpBackgrounds, IndexAtWhichToReplaceThirdUpBackground, ThirdUpBackgroundSprites);
	CheckForSpriteReplacement(SecondUpBackgrounds, IndexAtWhichToReplaceSecondUpBackground, SecondUpBackgroundSprites);
	CheckForSpriteReplacement(FirstUpBackgrounds, IndexAtWhichToReplaceFirstUpBackground, FirstUpBackgroundSprites,
							  FirstUpBackgroundSpawnCellSize, FirstUpBackgroundSpritesSpawnChance);
	CheckForSpriteReplacement(UpForegrounds, IndexAtWhichToReplaceUpForeground, ForegroundUpSprites,
							  UpForegroundSpritesCellSize, UpForegroundSpritesSpawnChance);
	CheckForSpriteReplacement(DownForegrounds, IndexAtWhichToReplaceDownForeground, ForegroundDownSprites,
							  DownForegroundSpritesCellSize, DownForegroundSpritesSpawnChance);
	CheckForSpriteReplacement(Dividers, 1, DividerSprites,
							  DividerCellSize);
	CheckForCollisionReplacement();
	CheckForBarricadeReplacement();

	SetActorRotation(FRotator(0.f, 0.f, FMath::FInterpTo(GetActorRotation().Roll, bUpperWorld ? 0.f : 180.f, DeltaTime, WorldTransitionSpeed)));

#define INTERPOLATE_ROOT_LOCATION(Member) \
	Member->SetRelativeLocation(FMath::VInterpTo(Member->GetRelativeLocation(), \
														 bUpperWorld \
															 ? GetDefault<ASceneManager>(GetClass())->Member->GetRelativeLocation() \
															 : -GetDefault<ASceneManager>(GetClass())->Member->GetRelativeLocation(), \
														 DeltaTime, WorldTransitionSpeed))

	INTERPOLATE_ROOT_LOCATION(ForegroundDividerRoot);
	INTERPOLATE_ROOT_LOCATION(ForegroundRoot);
	INTERPOLATE_ROOT_LOCATION(FirstBackgroundRoot);
	INTERPOLATE_ROOT_LOCATION(SecondBackgroundRoot);
	INTERPOLATE_ROOT_LOCATION(ThirdBackgroundRoot);
	INTERPOLATE_ROOT_LOCATION(FourthBackgroundRoot);

#undef INTERPOLATE_ROOT_LOCATION
}

FSpriteSpawn ASceneManager::GetRandomSpriteWithWeight(const TArray<FSpriteSpawn>& Array)
{
	float SpawnChanceTotal = 0.f;
	for (const FSpriteSpawn& It : Array)
	{
		SpawnChanceTotal += It.SpawnChance;
	}
	const float Rand = FMath::RandRange(0.f, SpawnChanceTotal);
	float Curr = 0.f;
	for (const FSpriteSpawn& It : Array)
	{
		Curr += It.SpawnChance;
		if (Rand <= Curr)
		{
			return It;
		}
	}

	return FSpriteSpawn();
}

void ASceneManager::PopulateSpriteComponentArray(TArray<UPaperSpriteComponent*>& Array, int32 NumerOfComponents, USceneComponent* Parent,
												 int32 Priority, bool bRotate)
{
	Array.Reserve(NumerOfComponents);
	for (int32 i = 0; i < NumerOfComponents; ++i)
	{
		UPaperSpriteComponent* NewComponent = NewObject<UPaperSpriteComponent>(this);
		NewComponent->RegisterComponent();
		NewComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AddInstanceComponent(NewComponent);
		NewComponent->SetTranslucentSortPriority(Priority);
		if (Parent)
		{
			NewComponent->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
		if (bRotate)
		{
			NewComponent->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
		}
		Array.Emplace(NewComponent);
	}
}

void ASceneManager::InitializeSpriteComponentArray(TArray<UPaperSpriteComponent*>& BackgroundsArray, const TArray<FSpriteSpawn>& Sprites,
												   float CellSize, float SpawnChance)
{
	if (Sprites.Num() > 0)
	{
		for (int32 i = 0; i < BackgroundsArray.Num(); ++i)
		{
			UPaperSpriteComponent* Background = BackgroundsArray[i];

			if (FMath::RandRange(0.f, 1.f) < SpawnChance)
			{
				const FSpriteSpawn Sprite = GetRandomSpriteWithWeight(Sprites);
				Background->SetSprite(Sprite.Sprite);
				Background->SetRelativeLocation(
					FVector(0.f, Background->GetRelativeLocation().Y, Sprite.HeightOffset));
			}
			else
			{
				Background->SetSprite(TestInvSprite);
			}
		}
		for (int32 i = 0; i < BackgroundsArray.Num(); ++i)
		{
			UPaperSpriteComponent* Background = BackgroundsArray[i];
			if (CellSize > 0.f)
			{
				Background->SetRelativeLocation(
					FVector(CellSize * i,
							Background->GetRelativeLocation().Y, Background->GetRelativeLocation().Z));
			}
			else
			{
				if (i != 0)
				{
					UPaperSpriteComponent* PrevBackground = BackgroundsArray[i - 1];
					Background->SetRelativeLocation(
						FVector(PrevBackground->GetRelativeLocation().X + PrevBackground->Bounds.BoxExtent.X + Background->Bounds.BoxExtent.X,
								Background->GetRelativeLocation().Y, Background->GetRelativeLocation().Z));
				}
				else
				{
					Background->SetRelativeLocation(
						FVector(0.f,
								Background->GetRelativeLocation().Y, Background->GetRelativeLocation().Z));
				}
			}
		}
	}
}

void ASceneManager::InitializeBarricades()
{
	Barricades.Reserve(MaxNumberOfBarricades);
	for (int32 i = 0; i < MaxNumberOfBarricades; ++i)
	{
		UPaperSpriteComponent* NewUpperBarricade = NewObject<UPaperSpriteComponent>(this);
		NewUpperBarricade->RegisterComponent();
		NewUpperBarricade->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AddInstanceComponent(NewUpperBarricade);
		NewUpperBarricade->SetTranslucentSortPriority(4);
		if (UpperBarricadesRoot)
		{
			NewUpperBarricade->AttachToComponent(UpperBarricadesRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
		UPaperSpriteComponent* NewDownBarricade = NewObject<UPaperSpriteComponent>(this);
		NewDownBarricade->RegisterComponent();
		NewDownBarricade->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AddInstanceComponent(NewDownBarricade);
		NewDownBarricade->SetTranslucentSortPriority(4);
		if (DownBarricadesRoot)
		{
			NewDownBarricade->AttachToComponent(DownBarricadesRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
		NewDownBarricade->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
		Barricades.Emplace(NewUpperBarricade, NewDownBarricade);
	}

	for (int32 i = 0; i < Barricades.Num(); ++i)
	{
		if (!Timings.IsValidIndex(LastUsedTiming))
		{
			LastUsedTiming = 0;
		}
		FSpriteSpawn UpperSprite = GetRandomSpriteWithWeight(UpperBarricadeSprites);
		Barricades[i].UpperBarricade->SetSprite(UpperSprite.Sprite);
		Barricades[i].UpperBarricade->SetTranslucentSortPriority(4);
		Barricades[i].UpperBarricade->SetRelativeLocation(FVector(PlayerCharacter->GetSpeed() * Timings[LastUsedTiming] + BarricadeOffset, 0.f, UpperSprite.HeightOffset));
		FSpriteSpawn DownSprite = GetRandomSpriteWithWeight(DownBarricadeSprites);
		Barricades[i].DownBarricade->SetSprite(DownSprite.Sprite);
		Barricades[i].DownBarricade->SetTranslucentSortPriority(4);
		Barricades[i].DownBarricade->SetRelativeLocation(FVector(PlayerCharacter->GetSpeed() * Timings[LastUsedTiming] + BarricadeOffset, 0.f, DownSprite.HeightOffset));

		++LastUsedTiming;
	}
}

void ASceneManager::CheckForSpriteReplacement(TArray<UPaperSpriteComponent*>& BackgroundsArray, int32 IndexToCheck,
											  const TArray<FSpriteSpawn>& Sprites, float CellSize, float SpawnChance)
{
	UPaperSpriteComponent* FirstBackground = BackgroundsArray.Last();
	UPaperSpriteComponent* CheckedBackground = BackgroundsArray[IndexToCheck];
	UPaperSpriteComponent* LastBackground = BackgroundsArray[0];
	if (PlayerCharacter->GetActorLocation().X - LastBackground->GetComponentLocation().X >
		CheckedBackground->GetComponentLocation().X - LastBackground->GetComponentLocation().X)
	{
		float SpriteHeight;
		if (FMath::RandRange(0.f, 1.f) < SpawnChance)
		{
			const FSpriteSpawn Sprite = GetRandomSpriteWithWeight(Sprites);
			LastBackground->SetSprite(Sprite.Sprite);

			SpriteHeight = Sprite.HeightOffset;
		}
		else
		{
#if WITH_EDITOR
			LastBackground->SetSprite(TestInvSprite);
#else
			LastBackground->SetSprite(nullptr);
#endif

			SpriteHeight = LastBackground->GetRelativeLocation().Z;
		}

		LastBackground->SetRelativeLocation(FVector(
			CellSize > 0.f
				? BackgroundsArray.Last()->GetRelativeLocation().X + CellSize
				: FirstBackground->GetRelativeLocation().X + FirstBackground->Bounds.BoxExtent.X + LastBackground->Bounds.BoxExtent.X,
			LastBackground->GetRelativeLocation().Y, SpriteHeight));

		BackgroundsArray.RemoveAt(0);
		BackgroundsArray.Emplace(LastBackground);
	}
}

void ASceneManager::CheckForCollisionReplacement()
{
	UBoxComponent* LastFloor = FloorCollisions[0];
	if (PlayerCharacter->GetActorLocation().X - LastFloor->GetComponentLocation().X >
		FloorCollisions.Last()->GetComponentLocation().X - LastFloor->GetComponentLocation().X)
	{
		LastFloor->SetRelativeLocation(FVector(FloorCollisions.Last()->GetRelativeLocation().X + 10000.f, 0.f, 0.f));

		FloorCollisions.RemoveAt(0);
		FloorCollisions.Emplace(LastFloor);
	}
}

void ASceneManager::CheckForBarricadeReplacement()
{
	FBarricade CheckedBarricade = Barricades[IndexAtWhichToReplaceBarricade];
	FBarricade LastBarricade = Barricades[0];
	if (PlayerCharacter->GetActorLocation().X - LastBarricade.UpperBarricade->GetComponentLocation().X >
		Barricades.Last().UpperBarricade->GetComponentLocation().X - CheckedBarricade.UpperBarricade->GetComponentLocation().X)
	{
		if (!Timings.IsValidIndex(LastUsedTiming))
		{
			LastUsedTiming = 0;
		}
		FSpriteSpawn UpperSprite = GetRandomSpriteWithWeight(UpperBarricadeSprites);
		FSpriteSpawn DownSprite = GetRandomSpriteWithWeight(DownBarricadeSprites);
		LastBarricade.UpperBarricade->SetRelativeLocation(FVector(Timings[LastUsedTiming] * PlayerCharacter->GetSpeed() + BarricadeOffset, 0.f, UpperSprite.HeightOffset));
		LastBarricade.UpperBarricade->SetSprite(UpperSprite.Sprite);
		LastBarricade.DownBarricade->SetRelativeLocation(FVector(Timings[LastUsedTiming] * PlayerCharacter->GetSpeed() + BarricadeOffset, 0.f, DownSprite.HeightOffset));
		LastBarricade.DownBarricade->SetSprite(DownSprite.Sprite);
		++LastUsedTiming;

		Barricades.RemoveAt(0);
		Barricades.Emplace(LastBarricade);
	}
}
