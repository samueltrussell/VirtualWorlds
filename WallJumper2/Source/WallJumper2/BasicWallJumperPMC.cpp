// Fill out your copyright notice in the Description page of Project Settings.

#include "WallJumper2.h"
#include "BasicWallJumperPMC.h"

void UBasicWallJumperPMC::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * _MoveSpeed;
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement Vector: %f, %f"), DesiredMovementThisFrame.X, DesiredMovementThisFrame.Z);
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}


