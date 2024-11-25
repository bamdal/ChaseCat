// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ChaseCatCharacter.generated.h"

class UJMS_AmbassadorWindow;
class UJMS_UI_DestinationComponent;
class UJMS_UI_DestinationUI;
class UJMS_MassGameInstance;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AChaseCatCharacter : public ACharacter
{
	GENERATED_BODY()


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* AttachArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HandAttachPoint;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** 대화 전용 매핑 컨택스트 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* TalkingMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftTiltAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RightTiltAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LeftClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RightClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FindDestinationAction;

	// 대화 넘기기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextTalkAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OutTalkAction;
	
public:
	AChaseCatCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D MoveVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D BeforeVector;

	UFUNCTION(BlueprintCallable)
	bool DetachedCat(bool start);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CapsuleHalfHeight = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CapsuleRadius = 100.f;


	UFUNCTION(BlueprintCallable)
	void SetIMCStartDialogueText();

	UFUNCTION(BlueprintCallable)
	void SetIMCEndDialogueText();
	
	UFUNCTION(BlueprintCallable)
	USceneComponent* GetHandAttachPoint();


protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UJMS_MassGameInstance* MassGI;

	UPROPERTY()
	TArray<UJMS_UI_DestinationComponent*> DestinationComponents;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	void ResetVector(const FInputActionValue& Value);
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Find_Interaction(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);

	void LeftTilt(const FInputActionValue& Value);

	void RightTilt(const FInputActionValue& Value);

	void LeftClick(const FInputActionValue& Value);

	void RightClick(const FInputActionValue& Value);
	
	void FindDestination(const FInputActionValue& Value);
	
	void NextTalk(const FInputActionValue& Value);

	void OutTalk(const FInputActionValue& Value);
	

	float WalkSpeed = 500.0f;

	float SprintSpeed = 800.0f;
	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	UFUNCTION(BlueprintCallable)
	void ChangeMappingContext(UInputMappingContext* ChangeIMC);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

