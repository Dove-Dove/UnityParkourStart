// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayController::APlayController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 이동 세팅
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.3f;

	GetCharacterMovement()->MaxWalkSpeed = playerSpeed;

	// SpringArm 생성
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;

	// Camera 생성
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	// 컨트롤 회전 비활성화
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}
// Called to bind functionality to input
void APlayController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayController::MoveForward);
	PlayerInputComponent->BindAxis("MoveHoriaontal", this, &APlayController::MoveHoriaontal);
	PlayerInputComponent->BindAxis("Turn", this, &APlayController::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayController::LookUp);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayController::ScanObject);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayController::RuningMove);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayController::RuningEnd);

}

// Called when the game starts or when spawned
void APlayController::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayController::Turn(float value)
{
	AddControllerYawInput(value);
}

void APlayController::LookUp(float value)
{
	AddControllerPitchInput(-value);
}

void APlayController::MoveForward(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void APlayController::MoveHoriaontal(float value)
{
	if (Controller && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void APlayController::RuningMove()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayController::RuningEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = playerSpeed;
}

void APlayController::ScanObject()
{
	FHitResult HitResult;  
	FVector Start = GetActorLocation();
	FVector Forward = GetActorForwardVector(); 
	FVector End = Start + Forward * ScenLen; 

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); 

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility, // 충돌 채널 (보통 Visibility 사용)
		Params
	);


	if (bHit)
	{
		UE_LOG(LogTemp, Log, TEXT("HitObjeecc"));
		AActor* HitObj = HitResult.GetActor();

		DrawDebugLine(GetWorld(), Start, HitResult.ImpactPoint, FColor::Red, false, 1.f, 0, 1.f);
		DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 10.f, FColor::Blue, false, 1.f);
	}

	//else
	//{
	//	Jump();
	//}
}
	
// Called every frame
void APlayController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



