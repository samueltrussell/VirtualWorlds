// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EndGate.generated.h"

UCLASS()
class WALLJUMPER2_API AEndGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGate();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* _pSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	class UAudioComponent* _pAudio;
	
};
