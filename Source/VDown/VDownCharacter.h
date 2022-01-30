// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VDownCharacter.generated.h"

UCLASS()
class VDOWN_API AVDownCharacter : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	class UCameraComponent* Camera;

public:
	AVDownCharacter();

	float GetSpeed() const { return Speed; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnChangeWorld();
	void OnJump();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float JumpHeight = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float JumpTime = 0.4f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCurveFloat* JumpCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ChangeWorldActionName = "ChangeWorld";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName JumpActionName = "Jump";

private:
	bool bJumping = false;
	float JumpStartTime;
	float JumpStartHeight;
	bool bSaveJump = false;
};
