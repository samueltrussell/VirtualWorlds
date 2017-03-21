// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicWallJumper.generated.h"

UCLASS()
class WALLJUMPER2_API ABasicWallJumper : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicWallJumper();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom")
	class AActor* _pStartPositionActor;

protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* _pSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _pSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _pCamera;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* _pSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _MaxVelX = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _ForceScalarX = 500000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _AirborneScalarX = 15000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _WallJumpScalar = 40000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _MaxVelZ = 750.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	float _ForceScalarZ = 800000.0f;
	
	void MoveRight(float value);

	void Climb(float value);

	//Movement Related booleans
	bool _OnWall = false;
	bool _OnFloor = false;
	float _JumpScalar = 1.0f;


};
