// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EndPiece.h"
#include "LeftBot.h"
#include "TopBot.h"
#include "Public/LeftTopBot.h"
#include "Public/EveryDirection.h"
#include "TheDemented/TheDementedCharacter.h"
#include "GenertaeMazeActor.generated.h"

UCLASS()
class THEDEMENTED_API AGenertaeMazeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenertaeMazeActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector initLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	float scale;

private:
	TSubclassOf<AEndPiece> CEndPiece;
	TSubclassOf<ATopBot> CTopBot;
	TSubclassOf<ALeftBot> CLeftBot;
	TSubclassOf<ALeftTopBot> CLeftTopBot;
	TSubclassOf<AEveryDirection> CEveryDirection;
	TSubclassOf<UClass> player;

	AActor* actors[100][100];
};
