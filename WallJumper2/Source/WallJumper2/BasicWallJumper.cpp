// Fill out your copyright notice in the Description page of Project Settings.

#include "WallJumper2.h"
#include "BasicWallJumper.h"
#include "PaperSpriteComponent.h"

#include "BasicWallJumperPMC.h"

// Sets default values
ABasicWallJumper::ABasicWallJumper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_pSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	_pSprite->SetSimulatePhysics(true);
	_pSprite->SetConstraintMode(EDOFMode::SixDOF);
	_pSprite->BodyInstance.bLockXRotation;
	_pSprite->BodyInstance.bLockYRotation;
	_pSprite->BodyInstance.bLockZRotation;
	_pSprite->BodyInstance.bLockYTranslation;

	RootComponent = _pSprite;

	// Use a spring arm to give the camera smooth, natural-feeling motion.
	_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	_pSpringArm->SetupAttachment(RootComponent);
	_pSpringArm->RelativeRotation = FRotator(0.f, -90.f, 0.f);
	_pSpringArm->SocketOffset = FVector(0.0f, 0.0f, 300.0f);
	_pSpringArm->TargetArmLength = 500.0f;
	_pSpringArm->bEnableCameraLag = true;
	_pSpringArm->CameraLagSpeed = 10.0f;

	// Create a camera and attach to our spring arm
	_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	_pCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	_pCamera->SetOrthoWidth(5000.0f);
	_pCamera->SetupAttachment(_pSpringArm, USpringArmComponent::SocketName);

	// Create and attach a sphere component to check for contact with stuff
	_pSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	_pSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	_pSphere->SetSphereRadius(115.0f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABasicWallJumper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicWallJumper::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TSet<AActor*> overlappingActors;
	_pSphere->GetOverlappingActors(overlappingActors);

	_OnWall = false;
	_OnFloor = false;

	for (auto& actor : overlappingActors)
	{
		if (actor->ActorHasTag(FName("Wall"))) {
			_OnWall = true;
			float xDiff = this->GetActorTransform().GetLocation().X - actor->GetActorTransform().GetLocation().X;
			_JumpScalar = (xDiff >= 0) ? 1.0f : -1.0f;
		}

		if (actor->ActorHasTag(FName("Floor"))) {
			_OnFloor = true;
		}

		if (actor->ActorHasTag(FName("Kill")) && _pStartPositionActor != nullptr) {
			this->TeleportTo(_pStartPositionActor->GetTransform().GetLocation(), this->GetActorTransform().Rotator());
			_pSprite->BodyInstance.SetLinearVelocity(FVector(0.0f, 0.0f, 0.0f), false);
		}
	}

}

void ABasicWallJumper::SetupPlayerInputComponent(class UInputComponent* i_InputComponent) 
{
	i_InputComponent->BindAxis("MoveRight", this, &ABasicWallJumper::MoveRight);
	i_InputComponent->BindAxis("Climb", this, &ABasicWallJumper::Climb);
}

void ABasicWallJumper::MoveRight(float value)
{
	if (value != 0.0f) {

		// If on the floor, allow rapid traversal
		if (_OnFloor) {

			FVector currentVel = _pSprite->BodyInstance.GetUnrealWorldVelocity();

			if (FMath::Abs(currentVel.X) < _MaxVelX) {
				_pSprite->BodyInstance.AddForce(FVector(1.0f, 0.0f, 0.0f) * _ForceScalarX * value);
			}
			else {
				FVector newVel = FVector(_MaxVelX * value, 0.0f, currentVel.Z);
				_pSprite->BodyInstance.SetLinearVelocity(newVel, false);
			}
		}
		// If climbing a wall...
		else if (_OnWall && !_OnFloor) {
			// ...allow an impulse type leap away from the wall...
			if (value == _JumpScalar) {
				FVector currentVel = _pSprite->BodyInstance.GetUnrealWorldVelocity();
				FVector newVel = FVector(_MaxVelX * value, 0.0f, currentVel.Z);
				_pSprite->BodyInstance.SetLinearVelocity(newVel, false);
			}
			// ...or a constant pressure push into the wall to slow descent.
			else {
				_pSprite->BodyInstance.AddForce(FVector(1.0f, 0.0f, 0.0f) * _WallJumpScalar * value);
			}
		}
		// If airborne, allow severely limited lateral control
		else {
			_pSprite->BodyInstance.AddForce(FVector(1.0f, 0.0f, 0.0f) * _AirborneScalarX * value);
		}
	}
}

void ABasicWallJumper::Climb(float value)
{

	if (value != 0.0f) {
		if (_OnWall) {
			FVector currentVel = _pSprite->BodyInstance.GetUnrealWorldVelocity();

			if (FMath::Abs(currentVel.Z) < _MaxVelZ) {
				_pSprite->BodyInstance.AddForce(FVector(0.0f, 0.0f, 1.0f) * _ForceScalarZ * value);
			}
			else {
				FVector newVel = FVector(currentVel.X, 0.0f, _MaxVelZ * value);
				_pSprite->BodyInstance.SetLinearVelocity(newVel, false);
			}
		}
		else if (!_OnWall && _OnFloor) {
			_pSprite->BodyInstance.AddForce(FVector(0.0f, 0.0f, 1.0f) * _ForceScalarZ * value);
		}
	}

}

void ABasicWallJumper::SetSpawnPoint(AActor* pNewSpawnPointActor) {
	_pStartPositionActor = pNewSpawnPointActor;
}
