// Copyright octopus7. All Rights Reserved.

#include "UTestPopupWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "UMGStyleLibrary.h"
#include "UMGStyleSubsystem.h"
#include "UTestPopupStyleAsset.h"

TSharedRef<SWidget> UTestPopupWidget::RebuildWidget() {
  // First build the UI hierarchy
  BuildUI();

  // Call parent to create the underlying Slate widget
  TSharedRef<SWidget> Widget = Super::RebuildWidget();

  return Widget;
}

void UTestPopupWidget::NativeConstruct() {
  Super::NativeConstruct();

  // Apply styles after the widget is fully constructed
  ApplyStyles();

  // Bind button click event
  if (OKButton) {
    OKButton->OnClicked.AddDynamic(this, &UTestPopupWidget::OnOKButtonClicked);
  }
}

void UTestPopupWidget::BuildUI() {
  // Create root overlay for centering
  UCanvasPanel *RootCanvas =
      WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
  RootCanvas->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  // SizeBox to constrain popup size
  PopupSizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
  PopupSizeBox->SetWidthOverride(400.f);
  PopupSizeBox->SetHeightOverride(200.f);

  // Create BackgroundBlur widget for frosted glass effect
  BackgroundBlurWidget = WidgetTree->ConstructWidget<UBackgroundBlur>(
      UBackgroundBlur::StaticClass());
  BackgroundBlurWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
  BackgroundBlurWidget->SetBlurStrength(
      10.0f); // Default value, will be overridden in ApplyStyles

  // Create Panel Border (popup container)
  PanelBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
  PanelBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  // Create vertical box to hold title and client areas
  UVerticalBox *MainVerticalBox =
      WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());

  // ===== Title Area =====
  TitleBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
  TitleBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  TitleTextBlock =
      WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
  TitleTextBlock->SetText(TitleText);
  TitleTextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  TitleBorder->SetContent(TitleTextBlock);

  // Add title to main layout (auto height)
  UVerticalBoxSlot *TitleSlot =
      MainVerticalBox->AddChildToVerticalBox(TitleBorder);
  TitleSlot->SetHorizontalAlignment(HAlign_Fill);
  TitleSlot->SetVerticalAlignment(VAlign_Top);

  // ===== Client Area =====
  ClientBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
  ClientBorder->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  UVerticalBox *ClientVerticalBox =
      WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass());

  // Message text
  MessageTextBlock =
      WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
  MessageTextBlock->SetText(MessageText);
  MessageTextBlock->SetAutoWrapText(true);
  MessageTextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  UVerticalBoxSlot *MessageSlot =
      ClientVerticalBox->AddChildToVerticalBox(MessageTextBlock);
  MessageSlot->SetHorizontalAlignment(HAlign_Fill);
  MessageSlot->SetVerticalAlignment(VAlign_Top);
  MessageSlot->SetPadding(FMargin(0.f, 0.f, 0.f, 16.f));

  // Spacer to push button to bottom
  USpacer *Spacer =
      WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
  Spacer->SetSize(FVector2D(0.f, 1.f));
  UVerticalBoxSlot *SpacerSlot =
      ClientVerticalBox->AddChildToVerticalBox(Spacer);
  SpacerSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

  // Button container (centered)
  UHorizontalBox *ButtonContainer = WidgetTree->ConstructWidget<UHorizontalBox>(
      UHorizontalBox::StaticClass());

  // Left spacer for centering
  USpacer *LeftSpacer =
      WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
  UHorizontalBoxSlot *LeftSpacerSlot =
      ButtonContainer->AddChildToHorizontalBox(LeftSpacer);
  LeftSpacerSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

  // OK Button with size box for minimum size
  USizeBox *ButtonSizeBox =
      WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
  ButtonSizeBox->SetMinDesiredWidth(100.f);
  ButtonSizeBox->SetMinDesiredHeight(36.f);

  OKButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());
  OKButton->SetVisibility(ESlateVisibility::Visible);

  OKButtonText =
      WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
  OKButtonText->SetText(FText::FromString(TEXT("OK")));
  OKButtonText->SetJustification(ETextJustify::Center);
  OKButtonText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

  OKButton->SetContent(OKButtonText);
  ButtonSizeBox->SetContent(OKButton);

  UHorizontalBoxSlot *ButtonSlot =
      ButtonContainer->AddChildToHorizontalBox(ButtonSizeBox);
  ButtonSlot->SetHorizontalAlignment(HAlign_Center);
  ButtonSlot->SetVerticalAlignment(VAlign_Center);

  // Right spacer for centering
  USpacer *RightSpacer =
      WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
  UHorizontalBoxSlot *RightSpacerSlot =
      ButtonContainer->AddChildToHorizontalBox(RightSpacer);
  RightSpacerSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

  UVerticalBoxSlot *ButtonContainerSlot =
      ClientVerticalBox->AddChildToVerticalBox(ButtonContainer);
  ButtonContainerSlot->SetHorizontalAlignment(HAlign_Fill);

  ClientBorder->SetContent(ClientVerticalBox);

  // Add client area to main layout (fills remaining space)
  UVerticalBoxSlot *ClientSlot =
      MainVerticalBox->AddChildToVerticalBox(ClientBorder);
  ClientSlot->SetHorizontalAlignment(HAlign_Fill);
  ClientSlot->SetVerticalAlignment(VAlign_Fill);
  ClientSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));

  // Set main vertical box as panel content
  PanelBorder->SetContent(MainVerticalBox);

  // Wrap PanelBorder with BackgroundBlur
  BackgroundBlurWidget->SetContent(PanelBorder);

  // Put background blur in size box
  PopupSizeBox->SetContent(BackgroundBlurWidget);

  // Add size box to canvas and center it
  UCanvasPanelSlot *PopupSlot = RootCanvas->AddChildToCanvas(PopupSizeBox);
  PopupSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
  PopupSlot->SetAlignment(FVector2D(0.5f, 0.5f));
  PopupSlot->SetAutoSize(true);

  // Set canvas as root widget
  WidgetTree->RootWidget = RootCanvas;
}

void UTestPopupWidget::ApplyStyles() {
  // Get style asset: prefer directly set StyleAsset, otherwise get from
  // subsystem
  UTestPopupStyleAsset *EffectiveStyle = StyleAsset;
  if (!EffectiveStyle) {
    if (UUMGStyleSubsystem *Subsystem =
            UUMGStyleLibrary::GetStyleSubsystem(this)) {
      EffectiveStyle = Subsystem->GetPopupStyleAsset();
    }
  }

  if (!EffectiveStyle) {
    return;
  }

  // Apply popup size
  if (PopupSizeBox) {
    PopupSizeBox->SetWidthOverride(EffectiveStyle->PopupSize.X);
    PopupSizeBox->SetHeightOverride(EffectiveStyle->PopupSize.Y);
  }

  // Apply background blur settings
  if (BackgroundBlurWidget) {
    if (EffectiveStyle->bEnableBackgroundBlur) {
      BackgroundBlurWidget->SetBlurStrength(
          EffectiveStyle->BackgroundBlurStrength);
      BackgroundBlurWidget->SetVisibility(
          ESlateVisibility::SelfHitTestInvisible);
    } else {
      BackgroundBlurWidget->SetBlurStrength(0.0f);
    }
  }

  // Apply panel style
  if (PanelBorder) {
    PanelBorder->SetBrush(EffectiveStyle->PanelBrush);
    PanelBorder->SetPadding(EffectiveStyle->PanelPadding);
  }

  // Apply title style
  if (TitleBorder) {
    TitleBorder->SetBrush(EffectiveStyle->TitleBackgroundBrush);
    TitleBorder->SetPadding(EffectiveStyle->TitlePadding);
  }

  if (TitleTextBlock) {
    TitleTextBlock->SetFont(EffectiveStyle->TitleFont);
    TitleTextBlock->SetColorAndOpacity(EffectiveStyle->TitleTextColor);
  }

  // Apply client area style
  if (ClientBorder) {
    ClientBorder->SetBrush(EffectiveStyle->ClientBackgroundBrush);
    ClientBorder->SetPadding(EffectiveStyle->ClientPadding);
  }

  // Apply message style
  if (MessageTextBlock) {
    MessageTextBlock->SetFont(EffectiveStyle->MessageFont);
    MessageTextBlock->SetColorAndOpacity(EffectiveStyle->MessageTextColor);
  }

  // Apply button style
  if (OKButton) {
    OKButton->SetStyle(EffectiveStyle->OKButtonStyle);
  }

  if (OKButtonText) {
    OKButtonText->SetFont(EffectiveStyle->ButtonFont);
    OKButtonText->SetColorAndOpacity(EffectiveStyle->ButtonTextColor);
  }
}

void UTestPopupWidget::OnOKButtonClicked() { ClosePopup(); }

void UTestPopupWidget::ClosePopup() { RemoveFromParent(); }
