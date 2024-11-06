// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JMS_Spawner.generated.h"

enum class E_ChildPoolName : uint8;

UCLASS()
class CHASECAT_API AJMS_Spawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool BeginSpawn = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SpawnArea = 500.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SpawnCount = 5;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 SpawnMulti = 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	E_ChildPoolName ObjectName;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float PoolLife = -1.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsLoop = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SpawnDelay = 1.0f;
public:	
	// Sets default values for this actor's properties
	AJMS_Spawner();

	UFUNCTION(BlueprintCallable)
	TArray<AJMS_ChildPawn*> StartMultiSpawning(E_ChildPoolName E_ObjectName, FVector Location, FRotator Rotation, int32 MultiCount, float Life);

	UFUNCTION(BlueprintCallable)
	AJMS_ChildPawn* Startspawning(E_ChildPoolName E_ObjectName, FVector Location, FRotator Rotation, float Life);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
