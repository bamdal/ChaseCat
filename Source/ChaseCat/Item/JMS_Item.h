// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JMS_Item.generated.h"

UCLASS()
class CHASECAT_API AJMS_Item : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJMS_Item();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent)
	bool StartGrab();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bPossibleGrab = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool bIsGrab = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName StartDialogueName = "";
	
	UFUNCTION(BlueprintCallable)
	void EndGrab();

	UFUNCTION(BlueprintCallable)
	void ThrowItem();

	UFUNCTION(BlueprintImplementableEvent)
	void ThrowItem_Implementation();

	UFUNCTION(BlueprintCallable)
	void Dissolve(float DissolveTime);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
