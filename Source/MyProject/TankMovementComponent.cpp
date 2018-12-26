// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::Initialize(UTankTrackComponent* _left, UTankTrackComponent* _right) {
	LeftTrack = _left;
	RightTrack = _right;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntentTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// Calculates the COS of the tanks current rotation against the rotation it wants to go
	// to produce a forward momentum
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);

	FVector TurnIntention = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntentTurnRight(TurnIntention.Z);


	//UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove called from tank %s"), *GetOwner()->GetName())
}
