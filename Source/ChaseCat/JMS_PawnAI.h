// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JMS_PawnAI.generated.h"

class UCapsuleComponent;

UCLASS()
class CHASECAT_API AJMS_PawnAI : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJMS_PawnAI();

public:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
