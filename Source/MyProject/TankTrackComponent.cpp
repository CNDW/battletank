// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"


UTankTrackComponent::UTankTrackComponent()
	: UStaticMeshComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysFriction();
	CurrentThrottle = 0.f;
}

void UTankTrackComponent::BeginPlay() 
{
	Super::BeginPlay();
}

void UTankTrackComponent::ApplySidewaysFriction()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto CorrectionAcceleration = SlippageSpeed / DeltaTime * -GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

	TankRoot->AddForce(CorrectionForce); 
}

void UTankTrackComponent::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(Throttle + CurrentThrottle, -1.f, 1.f);
}

void UTankTrackComponent::DriveTrack()
{
	auto ForceApplied = GetForwardVector()* CurrentThrottle* TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
