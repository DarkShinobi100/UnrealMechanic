// Fill out your copyright notice in the Description page of Project Settings.


#include "JetBoostActor.h"

// Sets default values
AJetBoostActor::AJetBoostActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJetBoostActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJetBoostActor::SaveHitObject(const UPrimitiveComponent* collider, bool& HasPhysics, FVector& ImpulseValue)
{
    //does what we hit have physics?
    if (collider->IsSimulatingPhysics())
    {
        HasPhysics = true;
        ImpulseValue = GetVelocity() * 100;
    }
    else
    {
        HasPhysics = false;
    }


}

void AJetBoostActor::StickToActor(const bool& AlreadyStuck, bool& StuckOn)
{

    if (AlreadyStuck == false)
    {    
        float LineTraceDistance = 100.f;

        FVector Start;
        FVector End;

        // get the camera view
        FVector CameraLoc = GetActorLocation();
        FRotator CameraRot = GetActorRotation();

        //save the start point to our camera's position
        Start = CameraLoc;

        //make forward vector 100 units long to hit far objects
        End = CameraLoc + (CameraRot.Vector() * LineTraceDistance);

        // extra information for the trace
        FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
        TraceParams.bTraceComplex = true;
        TraceParams.bReturnPhysicalMaterial = true;

        //Re-initialize hit info
        FHitResult HitDetails = FHitResult(ForceInit);

        bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitDetails,Start, End,ECC_GameTraceChannel3,TraceParams);
        // HitDetails will be filled with the info on what was hit by the trace

        if (bIsHit)
        {
            // something was hit
            
            //we can stick to it
            StuckOn = true;

            //print out what we hit
            UE_LOG(LogTemp, Warning, TEXT("We hit something"));

            //stick this actor to whoever we hit           
           AttachToActor(HitDetails.Actor.Get(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true));
           //set this actors location to where we hit
           SetActorLocation(HitDetails.ImpactPoint);            
        }
        else
        {
            // we missed try again
        }
    }
}

void AJetBoostActor::AllowUserInput()
{//Get player controller then allow input to be read from it   
   EnableInput(GetWorld()->GetFirstPlayerController());
}

void AJetBoostActor::ApplyImpulse(const bool& StuckOn, UPrimitiveComponent* HitActor, const bool& BoostActivate, const FVector& Impulse)
{
    if (HitActor != nullptr)
    {
        //check Collider is not null
        if (HitActor->IsPendingKillOrUnreachable())
        {
            //useless target
        }
        else
        {
            //apply impulse at location
            if (BoostActivate && StuckOn)
            {
                HitActor->AddImpulseAtLocation(Impulse, GetActorLocation());

            }
            else if (BoostActivate == false)
            {//turn off the thrust and have it gradually slow down
                FVector NoImpulse = { 0.0,0.0,0.0 };
                HitActor->AddImpulseAtLocation(NoImpulse, GetActorLocation());
            }
        }
    }

}

void AJetBoostActor::ToggleBoost(const bool& AlreadyActive, bool& ActivateBoost)
{
    //if boost already on turn off
    if (AlreadyActive)
    {
        ActivateBoost = false;
        SetLifeSpan(0.5f);
    }
    else //turn on
    {
        ActivateBoost = true;

    }
}

// Called every frame
void AJetBoostActor::Tick(float DeltaTime)
{ //used to applpy impulse to object once boost is enabled
	Super::Tick(DeltaTime);

}

