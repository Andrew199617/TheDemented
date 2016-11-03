// Fill out your copyright notice in the Description page of Project Settings.

#include "TheDemented.h"
#include "GenertaeMazeActor.h"
#include "GenerateMaze.h"
#include "AsciiFormats.h"
#include <string>

using std::string;

#define SPAWNENDPIECE(rotate) actors[j][i] = GetWorld()->SpawnActor<AEndPiece>(CEndPiece, \
FTransform( FRotator::MakeFromEuler(FVector(0, 0,rotate)) ,initLocation +  FVector(i * 400.0f * scale, j * -400.0f * scale, 0.0f ),FVector(scale))); \
actors[j][i]->SetActorRelativeScale3D(FVector(scale));

#define SPAWNTOPBOT(rotate) actors[j][i] = GetWorld()->SpawnActor<ATopBot>(CTopBot, \
FTransform(FRotator::MakeFromEuler(FVector(0, 0, rotate)),initLocation +  FVector(i * 400.0f * scale, j * -400.0f * scale, 0.0f), FVector(scale))); \
actors[j][i]->SetActorRelativeScale3D(FVector(scale));

#define SPAWNLEFTBOT(rotate) actors[j][i] = GetWorld()->SpawnActor<ALeftBot>(CLeftBot, \
FTransform(FRotator::MakeFromEuler(FVector(0, 0, rotate)),initLocation +  FVector(i * 400.0f * scale, j * -400.0f * scale, 0.0f), FVector(scale))); \
actors[j][i]->SetActorRelativeScale3D(FVector(scale));

#define SPAWNLEFTTOPBOT(rotate) actors[j][i] = GetWorld()->SpawnActor<ALeftTopBot>(CLeftTopBot, \
FTransform(FRotator::MakeFromEuler(FVector(0, 0, rotate)),initLocation +  FVector(i * 400.0f * scale, j * -400.0f * scale, 0.0f), FVector(scale))); \
actors[j][i]->SetActorRelativeScale3D(FVector(scale));

// Sets default values
AGenertaeMazeActor::AGenertaeMazeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	string path;
	string name;
	string my;
	string end;
	scale = 1;

	ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintObj(TEXT("Blueprint'/Game/MazePieces/DeadEnd.DeadEnd'"));
	if (BlueprintObj.Succeeded()) {
		CEndPiece = (UClass*)BlueprintObj.Object->GeneratedClass;
	}
	ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintObjTopBot(TEXT("Blueprint'/Game/MazePieces/TopBot.TopBot'"));
	if (BlueprintObjTopBot.Succeeded()) {
		CTopBot = (UClass*)BlueprintObjTopBot.Object->GeneratedClass;
	}
	ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintObjCLeftBot(TEXT("Blueprint'/Game/MazePieces/LeftBot.LeftBot'"));
	if (BlueprintObjCLeftBot.Succeeded()) {
		CLeftBot = (UClass*)BlueprintObjCLeftBot.Object->GeneratedClass;
	}
	ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintObjCLeftTopBot(TEXT("Blueprint'/Game/MazePieces/LeftTopBot.LeftTopBot'"));
	if (BlueprintObjCLeftTopBot.Succeeded()) {
		CLeftTopBot = (UClass*)BlueprintObjCLeftTopBot.Object->GeneratedClass;
	}
	ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintObjCEveryDirection(TEXT("Blueprint'/Game/MazePieces/EveryDirection.EveryDirection'"));
	if (BlueprintObjCEveryDirection.Succeeded()) {
		CEveryDirection = (UClass*)BlueprintObjCEveryDirection.Object->GeneratedClass;
	}
	ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintObjplayer(TEXT("Blueprint'/Game/Blueprints/TheDementedCharacter_BP.TheDementedCharacter_BP'"));
	if (BlueprintObjplayer.Succeeded()) {
		player = (UClass*)BlueprintObjplayer.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AGenertaeMazeActor::BeginPlay()
{
	Super::BeginPlay();
	GenerateMaze generateMaze(15, 15);
	
	MazeData* mazeData = generateMaze.GetMazeData();
	for (int i = 0; i < mazeData->m_Height; i++)
	{
		for (int j = 0; j < mazeData->m_Width; j++)
		{
			if (mazeData->startNode.x == j && mazeData->startNode.y == i)
			{
				//actors[j][i] = GetWorld()->SpawnActor<ATheDementedCharacter>(player, FTransform(FVector(i * 400.0f * scale, j * -400.0f * scale, 0.0f)));
			}
			else if (mazeData->exitNode.x == j && mazeData->exitNode.y == i)
			{
				actors[j][i] = GetWorld()->SpawnActor<AEndPiece>(CEndPiece, FVector(i * 400.0f * scale, j * -400.0f * scale, 800.0f * scale), FRotator::MakeFromEuler(FVector(0, 0, 0)));
			}
			else
			switch (mazeData->nodes[j][i].format)
			{
			case AsciiFormats::TopBot:
				SPAWNTOPBOT(0)
					break;
			case AsciiFormats::LeftRight:
				SPAWNTOPBOT(90)
					break;

			case AsciiFormats::LeftBot:
				SPAWNLEFTBOT(0)
					break;
			case AsciiFormats::LeftTop:
				SPAWNLEFTBOT(90)
					break;
			case AsciiFormats::TopRight:
				SPAWNLEFTBOT(180)
					break;
			case AsciiFormats::RightBot:
				SPAWNLEFTBOT(270)
					break;

			case AsciiFormats::TopLeftBot:
				SPAWNLEFTTOPBOT(0)
					break;
			case AsciiFormats::LeftRightTop:
				SPAWNLEFTTOPBOT(90)
					break;
			case AsciiFormats::TopRightBot:
				SPAWNLEFTTOPBOT(180)
					break;
			case AsciiFormats::LeftRightBot:
				SPAWNLEFTTOPBOT(270)
					break;

			case AsciiFormats::LeftRightBotTop:
				actors[j][i] = GetWorld()->SpawnActor<AEveryDirection>(CEveryDirection, FTransform(initLocation + FVector(i * 400.0f * scale, j * -400.0f * scale, 0.0f)));
				actors[j][i]->SetActorRelativeScale3D(FVector(scale));
				break;

			case AsciiFormats::HasBot:
				SPAWNENDPIECE(0)
					break;
			case AsciiFormats::HasLeft:
				SPAWNENDPIECE(90)
					break;
			case AsciiFormats::HasTop:
				SPAWNENDPIECE(180)
					break;
			case AsciiFormats::HasRight:
				SPAWNENDPIECE(270)
					break;
			}
		}
	}
	int meme = 0;
	
}

// Called every frame
void AGenertaeMazeActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

