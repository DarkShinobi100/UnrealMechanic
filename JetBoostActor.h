// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JetBoostActor.generated.h"

UCLASS()
class JETBOOSTERS_API AJetBoostActor : public AActor
{
	//Data
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector m_Impulse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  m_StuckOn = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  m_BoostActivate = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPrimitiveComponent* m_hitActor;
		
	//Functions
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJetBoostActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Check the object we hit has physics, save it if we do
	UFUNCTION(BlueprintCallable)
		void SaveHitObject(const UPrimitiveComponent* collider, bool& HasPhysics, FVector& ImpulseValue);

	//Use a ray trace to check if we can stick to anything
	UFUNCTION(BlueprintCallable)
		void StickToActor(const bool& AlreadyStuck, bool& StuckOn);

	//Allow us to use the player inputs
	UFUNCTION(BlueprintCallable)
		void AllowUserInput();

	//Apply force to object for Boost!
	UFUNCTION(BlueprintCallable)
		void ApplyImpulse(const bool& StuckOn, UPrimitiveComponent* HitActor, const bool& BoostActivate, const FVector& Impulse);

	//Turn on and off boosters
	UFUNCTION(BlueprintCallable)
		void ToggleBoost(const bool& AlreadyActive, bool& ActivateBoost);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
