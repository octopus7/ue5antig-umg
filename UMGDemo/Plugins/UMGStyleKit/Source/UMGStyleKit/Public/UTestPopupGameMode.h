// Copyright octopus7. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UTestPopupGameMode.generated.h"

/**
 * Test game mode that shows a popup on begin play.
 * Used for testing the UTestPopupWidget and style system.
 */
UCLASS()
class UMGSTYLEKIT_API ATestPopupGameMode : public AGameModeBase {
  GENERATED_BODY()

public:
  ATestPopupGameMode();

  /** Title text for the test popup */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Popup")
  FText PopupTitle = FText::FromString(TEXT("Test Popup"));

  /** Message text for the test popup */
  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Popup")
  FText PopupMessage = FText::FromString(
      TEXT("This is a test popup message.\nClick OK to close."));

protected:
  virtual void BeginPlay() override;

private:
  void ShowTestPopup();
};
