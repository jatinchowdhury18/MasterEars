#include "JuceHeader.h"
#include "MainComponent.h"

class MasterEarsApplication : public JUCEApplication
{
public:
    MasterEarsApplication() {}
    
    const String getApplicationName() override    { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override    { return true; }

    void initialise (const String& commandLine) override
    {
        // if (handleInternalCommandLineOperations (commandLine))
        //     return;
	
	mainWindow.reset (new MainWindow (getApplicationName(), commandLine));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow (String name, String mode) : DocumentWindow (name,
            Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId),
	    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
	    setContentOwned (new MainComponent, true);

	    setResizable (true, false);
	    centreWithSize (getWidth(), getHeight());

            setVisible (true);
        }

	void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (MasterEarsApplication)

