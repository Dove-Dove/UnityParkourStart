// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayController.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!player)
    {
        player = Cast<APlayController>(TryGetPawnOwner());
    }

    if (!player) return;

    // �ӵ� ���
    FVector Velocity = player->GetVelocity();
    Velocity.Z = 0; // Z�� ���� (���� �ӵ�)
    playerSpeed = Velocity.Size();


}
