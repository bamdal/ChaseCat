// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JMS_Interaction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJMS_Interaction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CHASECAT_API IJMS_Interaction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual void Interaction();
public:
};
