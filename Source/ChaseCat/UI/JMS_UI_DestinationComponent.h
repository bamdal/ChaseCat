// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JMS_UI_DestinationComponent.generated.h"


class UJMS_MassGameInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHASECAT_API UJMS_UI_DestinationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJMS_UI_DestinationComponent();

	// 고유 인덱스
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 Index = -1;

	UPROPERTY()
	UJMS_MassGameInstance* MGI;
	
	UFUNCTION(BlueprintCallable)
	bool FinishQuest();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
