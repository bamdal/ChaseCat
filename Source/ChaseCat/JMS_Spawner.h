// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JMS_Spawner.generated.h"

UCLASS()
class CHASECAT_API AJMS_Spawner : public AActor
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	bool BeginSpawn = true;

	UPROPERTY(EditAnywhere)
	float SpawnArea = 500.0f;

	UPROPERTY(EditAnywhere)
	int32 SpawnCount = 5;

	UPROPERTY(EditAnywhere)
	float PoolLife = -1.0f;

	UPROPERTY(EditAnywhere)
	bool IsLoop = false;
	
	UPROPERTY(EditAnywhere)
	float SpawnDelay = 1.0f;
public:	
	// Sets default values for this actor's properties
	AJMS_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
