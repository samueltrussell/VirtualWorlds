// Fill out your copyright notice in the Description page of Project Settings.

#include "WallJumper2.h"
#include "Checkpoint.h"

#include "PaperSpriteComponent.h"
#include "BasicWallJumper.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_pSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	_pSprite->SetSimulatePhysics(false);
	_pSprite->bGenerateOverlapEvents = false;

	_pSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	_pSphere->SetSphereRadius(230.0f);
	_pSphere->SetSimulatePhysics(false);
	_pSphere->bGenerateOverlapEvents = true;

	TScriptDelegate<FWeakObjectPtr> onBeginOverlapFunc;
	onBeginOverlapFunc.BindUFunction(this, "OnBeginOverlap");
	
	_pSphere->OnComponentBeginOverlap.Add(onBeginOverlapFunc);

	_pAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	_pAudio->bAutoActivate = false;
	_pAudio->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACheckpoint::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 

{
	ABasicWallJumper* const testActor = Cast<ABasicWallJumper>(OtherActor);

	if (testActor) {
		testActor->SetSpawnPoint(this);
		_pSprite->SetSpriteColor(FLinearColor(0.0f, 1.0f, 0.0f));
		_pAudio->Play();
	}
}