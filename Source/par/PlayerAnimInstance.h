// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PAR_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// �� ������ ����
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float playerSpeed;


	UPROPERTY(BlueprintReadOnly, Category = "Character")
	class APlayController* player;
};
