// Copyright octopus7. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateTypes.h"
#include "UTestPopupStyleAsset.generated.h"

/**
 * Data Asset for defining test popup widget styles.
 * Each style property controls a specific UI element in the popup.
 */
UCLASS(BlueprintType)
class UMGSTYLEKIT_API UTestPopupStyleAsset : public UDataAsset {
  GENERATED_BODY()

public:
  UTestPopupStyleAsset();

  // ========== Panel (Overall Popup Container) ==========

  /** Background brush for the entire popup panel */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Panel")
  FSlateBrush PanelBrush;

  /** Padding inside the panel */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Panel")
  FMargin PanelPadding = FMargin(0.f);

  /** Desired popup size (width x height) */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Panel")
  FVector2D PopupSize = FVector2D(400.f, 200.f);

  /** Enable background blur effect (frosted glass look) */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Panel")
  bool bEnableBackgroundBlur = true;

  /** Blur strength when background blur is enabled (0-100) */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Panel",
            meta = (EditCondition = "bEnableBackgroundBlur", ClampMin = "0.0",
                    ClampMax = "100.0"))
  float BackgroundBlurStrength = 10.0f;

  // ========== Title Area ==========

  /** Background brush for the title bar */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Title")
  FSlateBrush TitleBackgroundBrush;

  /** Font for title text */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Title")
  FSlateFontInfo TitleFont;

  /** Text color for title */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Title")
  FSlateColor TitleTextColor = FSlateColor(FLinearColor::White);

  /** Padding inside the title area */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Title")
  FMargin TitlePadding = FMargin(16.f, 10.f);

  // ========== Client Area ==========

  /** Background brush for the client area */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Client")
  FSlateBrush ClientBackgroundBrush;

  /** Padding inside the client area */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Client")
  FMargin ClientPadding = FMargin(20.f);

  // ========== Message Text ==========

  /** Font for message text */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Message")
  FSlateFontInfo MessageFont;

  /** Text color for message */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Message")
  FSlateColor MessageTextColor = FSlateColor(FLinearColor::White);

  // ========== OK Button ==========

  /** Style for the OK button */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
  FButtonStyle OKButtonStyle;

  /** Font for button text */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
  FSlateFontInfo ButtonFont;

  /** Text color for button */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
  FSlateColor ButtonTextColor = FSlateColor(FLinearColor::White);

  /** Minimum size for the button */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button")
  FVector2D ButtonMinSize = FVector2D(100.f, 36.f);
};
