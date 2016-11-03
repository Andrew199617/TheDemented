// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDemented.h"
#include "TopBot.h"


// Sets default values
ATopBot::ATopBot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATopBot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopBot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

