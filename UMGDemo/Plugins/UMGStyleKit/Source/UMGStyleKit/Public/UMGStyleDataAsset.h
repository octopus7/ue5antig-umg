// Copyright octopus7. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateColor.h"
#include "UMGStyleDataAsset.generated.h"


/**
 * Individual style entry containing visual properties
 */
USTRUCT(BlueprintType)
struct UMGSTYLEKIT_API FUMGStyleEntry {
  GENERATED_BODY()

  // Text styling
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
  FSlateFontInfo Font;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
  FSlateColor TextColor = FSlateColor(FLinearColor::White);

  // Background and border brushes
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brush")
  FSlateBrush BackgroundBrush;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brush")
  FSlateBrush BorderBrush;

  // Spacing
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
  FMargin Padding;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
  FMargin Margin;

  // Additional properties
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
  FVector2D MinSize = FVector2D::ZeroVector;

  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout")
  FVector2D MaxSize = FVector2D::ZeroVector;
};

/**
 * Data Asset for defining reusable UMG styles
 */
UCLASS(BlueprintType)
class UMGSTYLEKIT_API UUMGStyleDataAsset : public UDataAsset {
  GENERATED_BODY()

public:
  // Named styles map
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Styles")
  TMap<FName, FUMGStyleEntry> Styles;

  // Default/fallback style
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Styles")
  FUMGStyleEntry DefaultStyle;

  /**
   * Get a style by name, returns DefaultStyle if not found
   * @param StyleName The name of the style to retrieve
   * @return The style entry, or DefaultStyle if not found
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  const FUMGStyleEntry &GetStyle(FName StyleName) const;

  /**
   * Check if a style exists
   * @param StyleName The name of the style to check
   * @return True if the style exists
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  bool HasStyle(FName StyleName) const;
};
