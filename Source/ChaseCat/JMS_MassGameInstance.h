// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JMS_MassGameInstance.generated.h"

class AJMS_Spawner;
class AJMS_PoolFactory;
/**
 * 
 */
UCLASS()
class CHASECAT_API UJMS_MassGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool FactoryInit = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AJMS_PoolFactory> PoolFactoryClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AJMS_PoolFactory* PoolFactory;

	

	virtual void Init() override;

	void ReloadLevel(class UWorld* World);

	
};
