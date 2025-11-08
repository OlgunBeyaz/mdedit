#pragma once

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QString>

class QAction;
class MarkdownHighlighter;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void updatePreview();
    void showAbout();
    
    // Text editor functions
    void undoAction();
    void redoAction();
    void cutAction();
    void copyAction();
    void pasteAction();
    void findAction();
    void replaceAction();
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void toggleWordWrap();

private:
    void setupUi();
    void setupToolbar();
    void setupMenus();
    bool saveToFile(const QString &filePath);

    QString currentFile;
    QPlainTextEdit *editor;
    QTextEdit *preview;
    MarkdownHighlighter *highlighter;

    QAction *actionSave;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    
    int currentFontSize;
};
