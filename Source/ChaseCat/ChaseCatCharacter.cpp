// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChaseCatCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ISkeletonTreeItem.h"
#include "JMS_MassGameInstance.h"
#include "Interface/JMS_Interaction.h"
#include "UI/JMS_AmbassadorWindow.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AChaseCatCharacter

AChaseCatCharacter::AChaseCatCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	AttachArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("AttachArm"));
	AttachArm->SetupAttachment(RootComponent);
	AttachArm->TargetArmLength = 0.0f;	
	AttachArm->bUsePawnControlRotation = true;
	AttachArm->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));

	HandAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HandAttachPoint"));
	HandAttachPoint->SetupAttachment(AttachArm);
	HandAttachPoint->SetRelativeLocation(FVector(60.0f, 0.0f, 0.0f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AChaseCatCharacter::BeginPlay()
{
	// Call the base class  
	MassGI = Cast<UJMS_MassGameInstance>(GetWorld()->GetGameInstance());
	Super::BeginPlay();

}

void AChaseCatCharacter::ChangeMappingContext(UInputMappingContext* ChangeIMC)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Remove old contexts
			Subsystem->ClearAllMappings();
			// Add talking context
			Subsystem->AddMappingContext(ChangeIMC, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AChaseCatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChaseCatCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this,
		                                   &AChaseCatCharacter::ResetVector);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AChaseCatCharacter::Look);

		// Interaction
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this,
		                                   &AChaseCatCharacter::Find_Interaction);


		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AChaseCatCharacter::Sprint);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &AChaseCatCharacter::StopSprint);

		// Tilt
		EnhancedInputComponent->BindAction(LeftTiltAction, ETriggerEvent::Started, this, &AChaseCatCharacter::LeftTilt);
		EnhancedInputComponent->BindAction(RightTiltAction, ETriggerEvent::Started, this,
		                                   &AChaseCatCharacter::RightTilt);

		// Click
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &AChaseCatCharacter::LeftClick);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this,
										   &AChaseCatCharacter::RightClick);

		// FindDestination
		EnhancedInputComponent->BindAction(FindDestinationAction, ETriggerEvent::Started, this,
								   &AChaseCatCharacter::FindDestination);

		EnhancedInputComponent->BindAction(NextTalkAction, ETriggerEvent::Started, this, &AChaseCatCharacter::NextTalk);
		
		EnhancedInputComponent->BindAction(OutTalkAction, ETriggerEvent::Started, this, &AChaseCatCharacter::OutTalk);

		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}

}

/**
 * 전후, 좌우 키가 왕복으로 눌리는지 판단하는 함수
 * @param start 함수 실행여부
 * @return 떨어뜨리는 커멘드가 성공적으로 입력되었으면 true
 */
bool AChaseCatCharacter::DetachedCat(bool start)
{
	bool bDetached = false;
	if (start)
	{
		if (MoveVector != FVector2D::ZeroVector)
		{
			BeforeVector += MoveVector;
			if ((BeforeVector.IsZero() && !MoveVector.IsZero()) ||
				(MoveVector.X != 0 && BeforeVector.X == 0 && BeforeVector.Y != 0) ||
				(MoveVector.Y != 0 && BeforeVector.Y == 0 && BeforeVector.X != 0))
			{
				bDetached = true;
			}

			/*if(BeforeVector.X == 0 && BeforeVector.Y == 0)
			{
				bDetached = true;
			}
			if(MoveVector.X != 0 && BeforeVector.X == 0 && BeforeVector.Y != 0)
			{
				bDetached = true;
			}
			if(MoveVector.Y != 0 && BeforeVector.Y == 0 && BeforeVector.X != 0)
			{
				bDetached = true;
			}*/
		}

		BeforeVector = MoveVector;
	}
	return bDetached;
}



USceneComponent* AChaseCatCharacter::GetHandAttachPoint()
{
	if(HandAttachPoint->GetChildComponent(0) == nullptr)
	{
		return HandAttachPoint;
		
	}

	return nullptr;
}

void AChaseCatCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	MoveVector = MovementVector;
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);


		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AChaseCatCharacter::ResetVector(const FInputActionValue& Value)
{
	MoveVector = FVector2D::ZeroVector;
}

void AChaseCatCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

/**
 * 캐릭터의 전방에 탐색영역안에 Intercation 인터페이스가 있는지 체크후 있다면 상호작용
 * @param Value 
 */
void AChaseCatCharacter::Find_Interaction(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Display, TEXT("Interaction triggered"));
	
	TArray<FHitResult> HitResults;
	FVector CapsuleStart = this->K2_GetActorLocation() + this->GetActorForwardVector() * 100.0f;
	FVector CapsuleEnd = CapsuleStart + FVector(0, 0, CapsuleHalfHeight);
	
	// 트레이스 설정
	FCollisionQueryParams TraceParams(FName(TEXT("InteractionCapsuleTrace")), false, this);
	TraceParams.bReturnPhysicalMaterial = false;
	
	
	// 캡슐 트레이스 실행
	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		CapsuleStart,
		CapsuleEnd,
		FQuat::Identity,
		ECC_EngineTraceChannel2, // 또는 적합한 채널로 설정
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
		TraceParams
	);
	
#if UE_EDITOR
	if(MassGI->IsTest)
	{
		// 디버그 캡슐 그리기 (디버깅용)
		DrawDebugCapsule(
			GetWorld(),
			CapsuleStart,
			CapsuleHalfHeight,
			CapsuleRadius,
			FQuat::Identity,
			bHit ? FColor::Green : FColor::Red,
			false,
			2.0f
		);
	}
#endif
	if(bHit)
	{
		for (const FHitResult& HitResult : HitResults)
		{
			USceneComponent* HitComponent = HitResult.GetComponent()->GetAttachParent();;
			if(HitComponent && HitComponent->Implements<UJMS_Interaction>())
			{
				UE_LOG(LogTemplateCharacter, Display, TEXT("Find Interaction"));
				IJMS_Interaction::Execute_Interaction(HitComponent);
				break;
			}
			

		}
	}
}

void AChaseCatCharacter::Sprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AChaseCatCharacter::StopSprint(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AChaseCatCharacter::LeftTilt(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Display, TEXT("LeftTilt triggered"));
}

void AChaseCatCharacter::RightTilt(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Display, TEXT("Right tilt triggered"));
}

void AChaseCatCharacter::LeftClick(const FInputActionValue& Value)
{
}

void AChaseCatCharacter::RightClick(const FInputActionValue& Value)
{
}

void AChaseCatCharacter::FindDestination(const FInputActionValue& Value)
{

}

void AChaseCatCharacter::NextTalk(const FInputActionValue& Value)
{
	MassGI->NextTextDialogueFunc();
}

void AChaseCatCharacter::OutTalk(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,FString::Printf(TEXT("OutTalk triggered")));

	SetIMCEndDialogueText();
}

void AChaseCatCharacter::SetIMCStartDialogueText()
{
	ChangeMappingContext(TalkingMappingContext);
}

void AChaseCatCharacter::SetIMCEndDialogueText()
{
	ChangeMappingContext(DefaultMappingContext);
	MassGI->JMS_AmbassadorWindow->SetVisibility(ESlateVisibility::Hidden);
}
