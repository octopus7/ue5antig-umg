// Copyright octopus7. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMGStyleDataAsset.h"
#include "UMGStyleLibrary.generated.h"

class UUMGStyleSubsystem;
class UTextBlock;
class UBorder;
class UButton;
class UImage;

/**
 * Blueprint function library for UMG style operations
 */
UCLASS()
class UMGSTYLEKIT_API UUMGStyleLibrary : public UBlueprintFunctionLibrary {
  GENERATED_BODY()

public:
  /**
   * Get the UMG Style Subsystem
   * @param WorldContextObject Object to get world context from
   * @return The style subsystem, or nullptr
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style",
            meta = (WorldContext = "WorldContextObject"))
  static UUMGStyleSubsystem *
  GetStyleSubsystem(const UObject *WorldContextObject);

  /**
   * Get a style by name
   * @param WorldContextObject Object to get world context from
   * @param StyleName The name of the style
   * @return The style entry
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style",
            meta = (WorldContext = "WorldContextObject"))
  static FUMGStyleEntry GetStyle(const UObject *WorldContextObject,
                                 FName StyleName);

  /**
   * Apply style to a TextBlock widget
   * @param TextBlock The text block to style
   * @param Style The style to apply
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  static void ApplyStyleToTextBlock(UTextBlock *TextBlock,
                                    const FUMGStyleEntry &Style);

  /**
   * Apply style to a Border widget
   * @param Border The border to style
   * @param Style The style to apply
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  static void ApplyStyleToBorder(UBorder *Border, const FUMGStyleEntry &Style);

  /**
   * Apply style to a Button widget
   * @param Button The button to style
   * @param Style The style to apply
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  static void ApplyStyleToButton(UButton *Button, const FUMGStyleEntry &Style);

  /**
   * Apply style to an Image widget
   * @param Image The image to style
   * @param Style The style to apply
   */
  UFUNCTION(BlueprintCallable, Category = "UMG Style")
  static void ApplyStyleToImage(UImage *Image, const FUMGStyleEntry &Style);
};
