// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayController.generated.h"

UCLASS()
class PAR_API APlayController : public ACharacter
{
	GENERATED_BODY()

private:
	float playerSpeed = 300;
	float RunSpeed = 600;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float ScenLen = 70.f;
	
public:
	// Sets default values for this character's properties
	APlayController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Turn(float value);
	void LookUp(float value);
	void MoveForward(float value);
	void MoveHoriaontal(float value);
	void RuningMove();
	void RuningEnd();
    
	void ScanObject();
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
