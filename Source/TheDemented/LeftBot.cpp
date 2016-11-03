// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDemented.h"
#include "LeftBot.h"


// Sets default values
ALeftBot::ALeftBot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALeftBot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeftBot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

