#include "MainComponent.h"
#include "DataManager.h"

MainComponent::MainComponent() :
    settingsButton ("Audio Settings", DrawableButton::ImageFitted),
    logoButton ("Logo", DrawableButton::ImageFitted)
{
    setSize (850, 450);

    DataManager::getInstance();

    addAndMakeVisible (setupComponent);
    setupComponent.addListener (this);

    addAndMakeVisible (settingsButton);
    std::unique_ptr<Drawable> whiteGear (Drawable::createFromImageData
        (BinaryData::cogsolid_svg, BinaryData::cogsolid_svgSize));
    whiteGear->replaceColour (Colours::black, Colours::white);
    std::unique_ptr<Drawable> redGear (Drawable::createFromImageData
        (BinaryData::cogsolid_svg, BinaryData::cogsolid_svgSize));
    redGear->replaceColour (Colours::black, MyColours::red);
    settingsButton.setImages (whiteGear.get(), redGear.get(), redGear.get());
    settingsButton.onClick = [=] { DataManager::getInstance()->showAudioSettings(); };

    addAndMakeVisible (logoButton);
    auto logo = Drawable::createFromImageData (BinaryData::MasterEarsIcon_png, BinaryData::MasterEarsIcon_pngSize);
    logoButton.setImages (logo.get());
    logoButton.setMouseCursor (MouseCursor::PointingHandCursor);
    logoButton.onClick = [] { URL ("https://github.com/jatinchowdhury18/MasterEars").launchInDefaultBrowser(); };

    LookAndFeel::setDefaultLookAndFeel (&lnf);
}

MainComponent::~MainComponent()
{
    sessComponent.reset (nullptr);
    DataManager::deleteInstance();
}

void MainComponent::resized()
{
    const int top = getHeight() * 2 / 9;
    Rectangle<int> bounds (0, top, getWidth(), 3 * top);

    setupComponent.setBounds (bounds);
    if (sessComponent.get() != nullptr)
        sessComponent->setBounds (bounds);

    if (resComponent.get() != nullptr)
        resComponent->setBounds (bounds);

    const int pad = 5;
    const int buttonDim = top / 2 - pad * 2;
    settingsButton.setBounds (pad, bounds.getBottom() + pad, buttonDim, buttonDim);

    logoButton.setBounds (getWidth() - top + 2*pad, 2*pad,
        top - 4*pad, top - 4*pad);

    repaint();
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll (MyColours::black);

    const int top = getHeight() * 2 / 9;
    g.setColour (Colours::white);
    g.setFont (Font (float (top) / 2).boldened());
    g.drawFittedText ("MasterEars", 0, 0, getWidth(), top,
        Justification::centred, 1);
}

void MainComponent::setupComplete (Configuration* config)
{
    setupComponent.setVisible (false);
    
    sessComponent = std::make_unique<SessionComponent> (config);
    sessComponent->addListener (this);
    addAndMakeVisible (sessComponent.get());
    resized();
}

void MainComponent::sessionComplete (Logic* logic)
{
    sessComponent->setVisible (false);
    resComponent = std::make_unique<ResultsComponent> (logic);
    addAndMakeVisible (resComponent.get());
    resized();
}

