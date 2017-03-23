// Fill out your copyright notice in the Description page of Project Settings.

#include "WallJumper2.h"
#include "EndGate.h"

#include "PaperSpriteComponent.h"


// Sets default values
AEndGate::AEndGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_pSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	_pSprite->SetSimulatePhysics(false);

	TScriptDelegate<FWeakObjectPtr> onBeginOverlapFunc;
	onBeginOverlapFunc.BindUFunction(this, "OnBeginOverlap");

	_pSprite->OnComponentBeginOverlap.Add(onBeginOverlapFunc);

	_pAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioSource"));
	_pAudio->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEndGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndGate::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEndGate::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	AActor* testActor = Cast<AActor>(OtherActor);

	if (testActor) {
		_pAudio->Play();
	}
}



