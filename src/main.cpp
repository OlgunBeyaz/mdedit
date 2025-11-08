#include <QApplication>
#include <QTimer>
#include "MainWindow.h"
#include "SplashScreen.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application info
    app.setApplicationName("mdedit");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Kemal Akçocuk");
    app.setApplicationDisplayName("mdedit - Markdown Editor");
    
    // Show splash screen
    SplashScreen splash;
    splash.showSplash();
    
    // Create main window
    MainWindow w;
    w.resize(900, 600);
    
    // Show main window after splash
    QTimer::singleShot(2500, [&w]() {
        w.show();
    });
    
    return app.exec();
}
