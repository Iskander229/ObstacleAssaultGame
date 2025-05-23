// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	//log
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *GetName());
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

//return functions
bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > AllowedDistance;
}
float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

//voids
void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if(ShouldPlatformReturn())  
	{
		//set new start location to avoid overmoving with time.
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * AllowedDistance;
		SetActorLocation(StartLocation);
		//just everse the velocity 
		PlatformVelocity =- PlatformVelocity; 
	}
	else //move forward if didnt do 1 lap yet
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
