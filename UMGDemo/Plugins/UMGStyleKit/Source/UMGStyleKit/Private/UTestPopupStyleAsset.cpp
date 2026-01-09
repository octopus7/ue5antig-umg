// Copyright octopus7. All Rights Reserved.

#include "UTestPopupStyleAsset.h"

UTestPopupStyleAsset::UTestPopupStyleAsset() {
  // Color definitions (Pastel theme)
  // Base: Pastel beige #F5EBE0 -> RGB(245, 235, 224) / 255
  // Title: Pastel pink #FFD6E0 -> RGB(255, 214, 224) / 255
  // Button: Light brown #C4A484 -> RGB(196, 164, 132) / 255
  // Text: Dark brown #5D4037 -> RGB(93, 64, 55) / 255

  const FLinearColor PastelBeige(0.961f, 0.922f, 0.878f, 1.0f);
  const FLinearColor PastelPink(1.0f, 0.839f, 0.878f, 1.0f);
  const FLinearColor LightBrown(0.769f, 0.643f, 0.518f, 1.0f);
  const FLinearColor LightBrownHover(0.82f, 0.7f, 0.58f, 1.0f);
  const FLinearColor LightBrownPressed(0.7f, 0.58f, 0.45f, 1.0f);
  const FLinearColor DarkBrown(0.365f, 0.251f, 0.216f, 1.0f);
  const FLinearColor CreamWhite(0.98f, 0.96f, 0.94f, 1.0f);

  // Panel: Pastel beige with rounded corners
  PanelBrush.TintColor = FSlateColor(PastelBeige);
  PanelBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
  PanelBrush.OutlineSettings.CornerRadii = FVector4(8.f, 8.f, 8.f, 8.f);
  PanelBrush.OutlineSettings.RoundingType =
      ESlateBrushRoundingType::FixedRadius;

  // Title bar: Pastel pink (texture can be set in editor for dot pattern)
  TitleBackgroundBrush.TintColor = FSlateColor(PastelPink);
  TitleBackgroundBrush.DrawAs = ESlateBrushDrawType::Box;

  // Title text: Dark brown, bold
  TitleFont = FCoreStyle::GetDefaultFontStyle("Bold", 14);
  TitleTextColor = FSlateColor(DarkBrown);

  // Client area: Transparent (uses panel background)
  ClientBackgroundBrush.TintColor =
      FSlateColor(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
  ClientBackgroundBrush.DrawAs = ESlateBrushDrawType::NoDrawType;

  // Message text: Dark brown
  MessageFont = FCoreStyle::GetDefaultFontStyle("Regular", 12);
  MessageTextColor = FSlateColor(DarkBrown);

  // Button: Light brown with rounded corners
  FSlateBrush ButtonNormalBrush;
  ButtonNormalBrush.TintColor = FSlateColor(LightBrown);
  ButtonNormalBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
  ButtonNormalBrush.OutlineSettings.CornerRadii = FVector4(6.f, 6.f, 6.f, 6.f);
  ButtonNormalBrush.OutlineSettings.RoundingType =
      ESlateBrushRoundingType::FixedRadius;

  FSlateBrush ButtonHoveredBrush = ButtonNormalBrush;
  ButtonHoveredBrush.TintColor = FSlateColor(LightBrownHover);

  FSlateBrush ButtonPressedBrush = ButtonNormalBrush;
  ButtonPressedBrush.TintColor = FSlateColor(LightBrownPressed);

  OKButtonStyle.SetNormal(ButtonNormalBrush);
  OKButtonStyle.SetHovered(ButtonHoveredBrush);
  OKButtonStyle.SetPressed(ButtonPressedBrush);

  // Button text: Cream white (for contrast on brown button)
  ButtonFont = FCoreStyle::GetDefaultFontStyle("Bold", 12);
  ButtonTextColor = FSlateColor(CreamWhite);
}
