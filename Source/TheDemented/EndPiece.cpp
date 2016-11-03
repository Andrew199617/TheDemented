// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDemented.h"
#include "EndPiece.h"


// Sets default values
AEndPiece::AEndPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEndPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndPiece::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

