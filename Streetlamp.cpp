// Fill out your copyright notice in the Description page of Project Settings.


#include "Streetlamp.h"

// Sets default values
AStreetlamp::AStreetlamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStreetlamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStreetlamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

