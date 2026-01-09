// Copyright octopus7. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "UTestPopupWidget.generated.h"


class UTestPopupStyleAsset;
class UBorder;
class UTextBlock;
class UButton;
class UVerticalBox;
class USizeBox;

/**
 * Test popup widget demonstrating style asset integration.
 * UI is built in RebuildWidget(), not in NativeConstruct().
 *
 * Structure:
 * - Panel (outer border)
 *   - Title Area (border with title text)
 *   - Client Area (border containing message and OK button)
 */
UCLASS()
class UMGSTYLEKIT_API UTestPopupWidget : public UUserWidget {
  GENERATED_BODY()

public:
  /** Style asset to use for this popup */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Popup|Style")
  TObjectPtr<UTestPopupStyleAsset> StyleAsset;

  /** Title text displayed in the title bar */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Popup|Content")
  FText TitleText = FText::FromString(TEXT("Popup Title"));

  /** Message text displayed in the client area */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Popup|Content")
  FText MessageText = FText::FromString(TEXT("Message goes here."));

  /** Close this popup and remove from parent */
  UFUNCTION(BlueprintCallable, Category = "Popup")
  void ClosePopup();

protected:
  // Build UI structure in RebuildWidget, not NativeConstruct
  virtual TSharedRef<SWidget> RebuildWidget() override;

  virtual void NativeConstruct() override;

private:
  // Widget references (weak to avoid prevent GC issues)
  UPROPERTY()
  TObjectPtr<UBorder> PanelBorder;

  UPROPERTY()
  TObjectPtr<UBorder> TitleBorder;

  UPROPERTY()
  TObjectPtr<UTextBlock> TitleTextBlock;

  UPROPERTY()
  TObjectPtr<UBorder> ClientBorder;

  UPROPERTY()
  TObjectPtr<UTextBlock> MessageTextBlock;

  UPROPERTY()
  TObjectPtr<UButton> OKButton;

  UPROPERTY()
  TObjectPtr<UTextBlock> OKButtonText;

  /** Build the widget hierarchy */
  void BuildUI();

  /** Apply styles from StyleAsset to all widgets */
  void ApplyStyles();

  /** Button click handler */
  UFUNCTION()
  void OnOKButtonClicked();
};
