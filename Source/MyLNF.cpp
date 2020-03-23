#include "MyLNF.h"

MyLNF::MyLNF()
{
    nunitoSans = Typeface::createSystemTypefaceFor (BinaryData::NunitoSansRegular_ttf, BinaryData::NunitoSansRegular_ttfSize);
    nunitoSansBold = Typeface::createSystemTypefaceFor (BinaryData::NunitoSansBold_ttf, BinaryData::NunitoSansBold_ttfSize);

    setColour (ResizableWindow::backgroundColourId, MyColours::black);
    setColour (ComboBox::outlineColourId, Colours::white);
    setColour (ComboBox::backgroundColourId, Colours::transparentBlack);
    setColour (PopupMenu::backgroundColourId, MyColours::black);
    setColour (PopupMenu::highlightedBackgroundColourId, MyColours::blue);
    setColour (PopupMenu::highlightedTextColourId, MyColours::black);
    setColour (TextButton::buttonColourId, Colours::transparentBlack);
    setColour (BubbleComponent::backgroundColourId, MyColours::black);
    setColour (AlertWindow::backgroundColourId, MyColours::black);
    setColour (AlertWindow::outlineColourId, MyColours::blue);
    setColour (ProgressBar::foregroundColourId, MyColours::red);
    setColour (TextEditor::backgroundColourId, MyColours::black);
}

Typeface::Ptr MyLNF::getTypefaceForFont (const Font& font)
{
    if (font.isBold())
        return nunitoSansBold;

    return nunitoSans;
}

Font MyLNF::getTextButtonFont (TextButton&, int buttonHeight)
{
    return Font (float (buttonHeight) / 2);
}

Font MyLNF::getComboBoxFont (ComboBox& box)
{
    return Font (float (box.getHeight()) / 2);
}

Font MyLNF::getPopupMenuFont()
{
    return Font (20.0f);
}

Font MyLNF::getAlertWindowTitleFont()
{
    return Font (24.0f);
}

void MyLNF::drawButtonBackground (Graphics& g,
                                  Button& button,
                                  const Colour& backgroundColour,
                                  bool shouldDrawButtonAsHighlighted,
                                  bool shouldDrawButtonAsDown)
{
    auto cornerSize = 6.0f;
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                      .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = button.findColour (TextButton::buttonOnColourId);

    g.setColour (baseColour);

    auto flatOnLeft   = button.isConnectedOnLeft();
    auto flatOnRight  = button.isConnectedOnRight();
    auto flatOnTop    = button.isConnectedOnTop();
    auto flatOnBottom = button.isConnectedOnBottom();

    if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
    {
        Path path;
        path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                  bounds.getWidth(), bounds.getHeight(),
                                  cornerSize, cornerSize,
                                  ! (flatOnLeft  || flatOnTop),
                                  ! (flatOnRight || flatOnTop),
                                  ! (flatOnLeft  || flatOnBottom),
                                  ! (flatOnRight || flatOnBottom));

        g.fillPath (path);

        g.setColour (button.findColour (ComboBox::outlineColourId));
        g.strokePath (path, PathStrokeType (1.0f));
    }
    else
    {
        g.fillRoundedRectangle (bounds, cornerSize);

        g.setColour (button.findColour (ComboBox::outlineColourId));
        g.drawRoundedRectangle (bounds, cornerSize, 1.0f);
    }
}

void MyLNF::drawButtonText (Graphics& g, TextButton& button,
                                     bool highlighted, bool /*down*/)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    bool colourBool = button.getToggleState() || highlighted;
    g.setColour (button.findColour (colourBool ? TextButton::textColourOnId
                                                            : TextButton::textColourOffId)
                       .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;

    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                          Justification::centred, 2);
}

void MyLNF::drawToggleButton (Graphics& g, ToggleButton& button,
                                       bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto fontSize = float (button.getHeight()) / 2;
    auto tickWidth = fontSize * 1.1f;

    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 shouldDrawButtonAsHighlighted,
                 shouldDrawButtonAsDown);

    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (fontSize);

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    g.drawFittedText (button.getButtonText(),
                      button.getLocalBounds().withTrimmedLeft (roundToInt (tickWidth) + 10)
                                             .withTrimmedRight (2),
                      Justification::centredLeft, 10);
}

void MyLNF::drawProgressBar (Graphics& g, ProgressBar& progressBar,
                                            int width, int height,
                                            double progress, const String& textToShow)
{
    auto background = progressBar.findColour (ProgressBar::backgroundColourId);
    auto foreground = progressBar.findColour (ProgressBar::foregroundColourId);

    auto barBounds = progressBar.getLocalBounds().toFloat();

    g.setColour (background);
    g.fillRoundedRectangle (barBounds, progressBar.getHeight() * 0.5f);

    if (progress >= 0.0f && progress <= 1.0f)
    {
        Path p;
        p.addRoundedRectangle (barBounds, progressBar.getHeight() * 0.5f);
        g.reduceClipRegion (p);

        barBounds.setWidth (barBounds.getWidth() * (float) progress);
        g.setColour (foreground);
        g.fillRoundedRectangle (barBounds, progressBar.getHeight() * 0.5f);
    }
    else
    {
        // spinning bar..
        g.setColour (background);

        auto stripeWidth = height * 2;
        auto position = static_cast<int> (Time::getMillisecondCounter() / 15) % stripeWidth;

        Path p;

        for (auto x = static_cast<float> (-position); x < width + stripeWidth; x += stripeWidth)
            p.addQuadrilateral (x, 0.0f,
                                x + stripeWidth * 0.5f, 0.0f,
                                x, static_cast<float> (height),
                                x - stripeWidth * 0.5f, static_cast<float> (height));

        Image im (Image::ARGB, width, height, true);

        {
            Graphics g2 (im);
            g2.setColour (foreground);
            g2.fillRoundedRectangle (barBounds, progressBar.getHeight() * 0.5f);
        }

        g.setTiledImageFill (im, 0, 0, 0.85f);
        g.fillPath (p);
    }

    if (textToShow.isNotEmpty())
    {
        g.setColour (Colours::white);
        g.setFont (Font (height * 0.8f));

        g.drawText (textToShow, 0, 0, width, height, Justification::centred, false);
    }
}
