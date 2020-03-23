#include "JuceHeader.h"
#include "MainComponent.h"
#include "MyLNF.h"

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
        MainWindow (String name, String mode) : DocumentWindow (name, MyColours::black,
	        DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
	        setContentOwned (new MainComponent, true);

	        setResizable (true, false);
	        centreWithSize (getWidth(), getHeight());

            auto screen = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
            setResizeLimits (getWidth() / 2, getHeight() - 150,
                screen.getWidth(), screen.getHeight());

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
