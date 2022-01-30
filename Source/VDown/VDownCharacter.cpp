// Fill out your copyright notice in the Description page of Project Settings.


#include "VDownCharacter.h"

#include "SceneManager.h"
#include "VDownGameMode.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


AVDownCharacter::AVDownCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USkeletalMeshComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
}

void AVDownCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AVDownCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(FVector(Speed * DeltaTime, 0.f, 0.f));

	if (bJumping)
	{
		float TimeFromJumpStart = GetWorld()->GetTimeSeconds() - JumpStartTime;
		if (TimeFromJumpStart > JumpTime)
		{
			bJumping = false;
			if (bSaveJump)
			{
				bSaveJump = false;
				OnJump();
			}
		}

		const float TimeNormalized = TimeFromJumpStart / JumpTime;
		Mesh->SetRelativeLocation(FVector(Mesh->GetRelativeLocation().X, Mesh->GetRelativeLocation().Y,
										  JumpStartHeight + JumpCurve->GetFloatValue(TimeNormalized) * JumpHeight));
	}
}

void AVDownCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(ChangeWorldActionName, EInputEvent::IE_Pressed, this, &AVDownCharacter::OnChangeWorld);
	PlayerInputComponent->BindAction(JumpActionName, EInputEvent::IE_Pressed, this, &AVDownCharacter::OnJump);
}

void AVDownCharacter::OnChangeWorld()
{
	UVDownHelpers::GetVDownGameMode(this)->GetSceneManager()->ChangeWorld();
}

void AVDownCharacter::OnJump()
{
	if (!bJumping)
	{
		bJumping = true;
		JumpStartTime = GetWorld()->GetTimeSeconds();
		JumpStartHeight = Mesh->GetRelativeLocation().Z;
	}
	else
	{
		bSaveJump = true;
	}
}
