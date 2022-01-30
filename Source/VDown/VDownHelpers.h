// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VDownHelpers.generated.h"

/**
 * 
 */
UCLASS()
class VDOWN_API UVDownHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template<typename Type>
	static Type& GetRandElement(TArray<Type>& Array)
	{
		check(Array.Num() > 0);
		return Array[FMath::RandRange(0, Array.Num() - 1)];
	}

	template<typename Type>
	static const Type& GetRandElement(const TArray<Type>& Array)
	{
		check(Array.Num() > 0);
		return Array[FMath::RandRange(0, Array.Num() - 1)];
	}

	static class AVDownGameMode* GetVDownGameMode(const UObject* Context);
};
