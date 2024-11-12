// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JMS_SpawnerTrigger.generated.h"

class UCapsuleComponent;
class AJMS_Spawner;

UCLASS()
class CHASECAT_API AJMS_SpawnerTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMS_SpawnerTrigger();


	UPROPERTY(EditAnywhere)
	AJMS_Spawner* GetSpawner;

	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY()
	UCapsuleComponent* Capsule;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
