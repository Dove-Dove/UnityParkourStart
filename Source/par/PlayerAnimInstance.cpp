// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APawn* Pawn = TryGetPawnOwner();
    if (!Pawn) return;

    playerSpeed = Pawn->GetVelocity().Size2D();

    ACharacter* Char = Cast<ACharacter>(Pawn);


}
