// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "BasicWallJumperPMC.generated.h"

/**
 * 
 */
UCLASS()
class WALLJUMPER2_API UBasicWallJumperPMC : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _MoveSpeed = 450.0f;
	
};
