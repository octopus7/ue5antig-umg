// Copyright octopus7. All Rights Reserved.

#include "UTestPopupGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UTestPopupWidget.h"

ATestPopupGameMode::ATestPopupGameMode() {}

void ATestPopupGameMode::BeginPlay() {
  Super::BeginPlay();

  // Show popup after a brief delay to ensure UI is ready
  GetWorldTimerManager().SetTimerForNextTick(
      this, &ATestPopupGameMode::ShowTestPopup);
}

void ATestPopupGameMode::ShowTestPopup() {
  APlayerController *PC = UGameplayStatics::GetPlayerController(this, 0);
  if (!PC) {
    return;
  }

  UTestPopupWidget *Popup =
      CreateWidget<UTestPopupWidget>(PC, UTestPopupWidget::StaticClass());
  if (Popup) {
    Popup->TitleText = PopupTitle;
    Popup->MessageText = PopupMessage;
    Popup->AddToViewport(100);

    // Set input mode to UI only
    FInputModeUIOnly InputMode;
    InputMode.SetWidgetToFocus(Popup->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PC->SetInputMode(InputMode);
    PC->bShowMouseCursor = true;
  }
}
