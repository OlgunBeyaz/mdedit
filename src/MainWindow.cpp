#include "MainWindow.h"
#include "MarkdownHighlighter.h"

#include <QApplication>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplitter>
#include <QTextStream>
#include <QTextDocument>
#include <QFont>
#include <QToolBar>
#include <QInputDialog>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), editor(new QPlainTextEdit(this)), preview(new QTextEdit(this)), 
      highlighter(nullptr), actionSave(nullptr), currentFontSize(14)
{
    setupUi();
    setupToolbar();
    setupMenus();
    updatePreview();
}

void MainWindow::setupUi()
{
    // Central splitter: left editor, right preview
    QSplitter *splitter = new QSplitter(this);
    
    // Professional editor styling
    editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    editor->setFont(QFont("Monaco, Menlo, 'Ubuntu Mono', monospace", 14));
    editor->setTabStopDistance(40); // 4 spaces tab width
    
    // Editor styling like VSCode
    editor->setStyleSheet(
        "QPlainTextEdit {"
        "  background-color: #1e1e1e;"
        "  color: #d4d4d4;"
        "  border: none;"
        "  padding: 10px;"
        "  font-family: 'Monaco', 'Menlo', 'Ubuntu Mono', 'Consolas', monospace;"
        "  font-size: 14px;"
        "  line-height: 1.5;"
        "  selection-background-color: #264f78;"
        "}"
        "QScrollBar:vertical {"
        "  background-color: #1e1e1e;"
        "  width: 12px;"
        "  border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background-color: #424242;"
        "  min-height: 20px;"
        "  border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "  background-color: #4f4f4f;"
        "}"
    );
    
    splitter->addWidget(editor);

    // Professional preview styling
    preview->setReadOnly(true);
    preview->setAcceptRichText(true);
    preview->setStyleSheet(
        "QTextEdit {"
        "  background-color: #ffffff;"
        "  border: none;"
        "  padding: 0px;"
        "}"
        "QScrollBar:vertical {"
        "  background-color: #f6f8fa;"
        "  width: 12px;"
        "  border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical {"
        "  background-color: #d0d7de;"
        "  min-height: 20px;"
        "  border-radius: 6px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "  background-color: #b1b9c1;"
        "}"
    );
    
    splitter->addWidget(preview);

    // Setup syntax highlighting for editor
    highlighter = new MarkdownHighlighter(editor->document());

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);
    splitter->setHandleWidth(3);
    splitter->setStyleSheet(
        "QSplitter {"
        "  background-color: #e1e4e8;"
        "}"
        "QSplitter::handle {"
        "  background-color: #e1e4e8;"
        "}"
        "QSplitter::handle:hover {"
        "  background-color: #0969da;"
        "}"
    );
    
    setCentralWidget(splitter);
}

void MainWindow::setupMenus()
{
    // File menu actions
    QAction *actionNew = new QAction(tr("Neu"), this);
    QAction *actionOpen = new QAction(tr("Öffnen..."), this);
    actionSave = new QAction(tr("Speichern"), this);
    QAction *actionSaveAs = new QAction(tr("Speichern als..."), this);
    QAction *actionQuit = new QAction(tr("Beenden"), this);

    actionSave->setShortcut(QKeySequence::Save);
    actionNew->setShortcut(QKeySequence::New);
    actionOpen->setShortcut(QKeySequence::Open);

    connect(actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(actionSaveAs, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(actionQuit, &QAction::triggered, this, &QWidget::close);

    // Edit menu actions
    actionUndo = new QAction(tr("Rückgängig"), this);
    actionRedo = new QAction(tr("Wiederholen"), this);
    actionCut = new QAction(tr("Ausschneiden"), this);
    actionCopy = new QAction(tr("Kopieren"), this);
    actionPaste = new QAction(tr("Einfügen"), this);
    QAction *actionFind = new QAction(tr("Suchen..."), this);
    QAction *actionReplace = new QAction(tr("Ersetzen..."), this);

    actionUndo->setShortcut(QKeySequence::Undo);
    actionRedo->setShortcut(QKeySequence::Redo);
    actionCut->setShortcut(QKeySequence::Cut);
    actionCopy->setShortcut(QKeySequence::Copy);
    actionPaste->setShortcut(QKeySequence::Paste);
    actionFind->setShortcut(QKeySequence::Find);
    actionReplace->setShortcut(QKeySequence::Replace);

    connect(actionUndo, &QAction::triggered, this, &MainWindow::undoAction);
    connect(actionRedo, &QAction::triggered, this, &MainWindow::redoAction);
    connect(actionCut, &QAction::triggered, this, &MainWindow::cutAction);
    connect(actionCopy, &QAction::triggered, this, &MainWindow::copyAction);
    connect(actionPaste, &QAction::triggered, this, &MainWindow::pasteAction);
    connect(actionFind, &QAction::triggered, this, &MainWindow::findAction);
    connect(actionReplace, &QAction::triggered, this, &MainWindow::replaceAction);

    // View menu actions
    QAction *actionZoomIn = new QAction(tr("Vergrößern"), this);
    QAction *actionZoomOut = new QAction(tr("Verkleinern"), this);
    QAction *actionResetZoom = new QAction(tr("Zoom zurücksetzen"), this);
    QAction *actionWordWrap = new QAction(tr("Zeilenumbruch"), this);
    actionWordWrap->setCheckable(true);
    actionWordWrap->setChecked(true);

    actionZoomIn->setShortcut(QKeySequence::ZoomIn);
    actionZoomOut->setShortcut(QKeySequence::ZoomOut);

    connect(actionZoomIn, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(actionZoomOut, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(actionResetZoom, &QAction::triggered, this, &MainWindow::resetZoom);
    connect(actionWordWrap, &QAction::triggered, this, &MainWindow::toggleWordWrap);

    // Create menus
    QMenu *fileMenu = menuBar()->addMenu(tr("Datei"));
    fileMenu->addAction(actionNew);
    fileMenu->addAction(actionOpen);
    fileMenu->addSeparator();
    fileMenu->addAction(actionSave);
    fileMenu->addAction(actionSaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(actionQuit);

    QMenu *editMenu = menuBar()->addMenu(tr("Bearbeiten"));
    editMenu->addAction(actionUndo);
    editMenu->addAction(actionRedo);
    editMenu->addSeparator();
    editMenu->addAction(actionCut);
    editMenu->addAction(actionCopy);
    editMenu->addAction(actionPaste);
    editMenu->addSeparator();
    editMenu->addAction(actionFind);
    editMenu->addAction(actionReplace);

    QMenu *viewMenu = menuBar()->addMenu(tr("Ansicht"));
    viewMenu->addAction(actionZoomIn);
    viewMenu->addAction(actionZoomOut);
    viewMenu->addAction(actionResetZoom);
    viewMenu->addSeparator();
    viewMenu->addAction(actionWordWrap);

    // Help menu
    QAction *actionAbout = new QAction(tr("Über mdedit..."), this);
    connect(actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
    
    QMenu *helpMenu = menuBar()->addMenu(tr("Hilfe"));
    helpMenu->addAction(actionAbout);

    // Live preview: update on text changes
    connect(editor, &QPlainTextEdit::textChanged, this, &MainWindow::updatePreview);
}

void MainWindow::setupToolbar()
{
    QToolBar *toolbar = addToolBar(tr("Werkzeuge"));
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolbar->setStyleSheet(
        "QToolBar {"
        "  background-color: #f6f8fa;"
        "  border-bottom: 1px solid #d0d7de;"
        "  spacing: 5px;"
        "  padding: 5px;"
        "}"
        "QToolButton {"
        "  background-color: transparent;"
        "  border: 1px solid transparent;"
        "  border-radius: 6px;"
        "  padding: 5px;"
        "  margin: 2px;"
        "}"
        "QToolButton:hover {"
        "  background-color: #f3f4f6;"
        "  border: 1px solid #d0d7de;"
        "}"
        "QToolButton:pressed {"
        "  background-color: #e1e4e8;"
        "}"
    );

    // File actions
    QAction *toolNew = new QAction("📄", this);
    toolNew->setToolTip(tr("Neue Datei (Ctrl+N)"));
    connect(toolNew, &QAction::triggered, this, &MainWindow::newFile);
    toolbar->addAction(toolNew);

    QAction *toolOpen = new QAction("📂", this);
    toolOpen->setToolTip(tr("Öffnen (Ctrl+O)"));
    connect(toolOpen, &QAction::triggered, this, &MainWindow::openFile);
    toolbar->addAction(toolOpen);

    QAction *toolSave = new QAction("💾", this);
    toolSave->setToolTip(tr("Speichern (Ctrl+S)"));
    connect(toolSave, &QAction::triggered, this, &MainWindow::saveFile);
    toolbar->addAction(toolSave);

    toolbar->addSeparator();

    // Edit actions
    QAction *toolUndo = new QAction("↶", this);
    toolUndo->setToolTip(tr("Rückgängig (Ctrl+Z)"));
    connect(toolUndo, &QAction::triggered, this, &MainWindow::undoAction);
    toolbar->addAction(toolUndo);

    QAction *toolRedo = new QAction("↷", this);
    toolRedo->setToolTip(tr("Wiederholen (Ctrl+Y)"));
    connect(toolRedo, &QAction::triggered, this, &MainWindow::redoAction);
    toolbar->addAction(toolRedo);

    toolbar->addSeparator();

    QAction *toolCut = new QAction("✂️", this);
    toolCut->setToolTip(tr("Ausschneiden (Ctrl+X)"));
    connect(toolCut, &QAction::triggered, this, &MainWindow::cutAction);
    toolbar->addAction(toolCut);

    QAction *toolCopy = new QAction("📋", this);
    toolCopy->setToolTip(tr("Kopieren (Ctrl+C)"));
    connect(toolCopy, &QAction::triggered, this, &MainWindow::copyAction);
    toolbar->addAction(toolCopy);

    QAction *toolPaste = new QAction("📌", this);
    toolPaste->setToolTip(tr("Einfügen (Ctrl+V)"));
    connect(toolPaste, &QAction::triggered, this, &MainWindow::pasteAction);
    toolbar->addAction(toolPaste);

    toolbar->addSeparator();

    // Zoom actions
    QAction *toolZoomIn = new QAction("🔍+", this);
    toolZoomIn->setToolTip(tr("Vergrößern (Ctrl++)"));
    connect(toolZoomIn, &QAction::triggered, this, &MainWindow::zoomIn);
    toolbar->addAction(toolZoomIn);

    QAction *toolZoomOut = new QAction("🔍-", this);
    toolZoomOut->setToolTip(tr("Verkleinern (Ctrl+-)"));
    connect(toolZoomOut, &QAction::triggered, this, &MainWindow::zoomOut);
    toolbar->addAction(toolZoomOut);

    QAction *toolResetZoom = new QAction("🔍=", this);
    toolResetZoom->setToolTip(tr("Zoom zurücksetzen"));
    connect(toolResetZoom, &QAction::triggered, this, &MainWindow::resetZoom);
    toolbar->addAction(toolResetZoom);

    toolbar->addSeparator();

    // Find action
    QAction *toolFind = new QAction("🔍", this);
    toolFind->setToolTip(tr("Suchen (Ctrl+F)"));
    connect(toolFind, &QAction::triggered, this, &MainWindow::findAction);
    toolbar->addAction(toolFind);
}

void MainWindow::newFile()
{
    if (!currentFile.isEmpty()) {
        // offer to save current
        QMessageBox::StandardButton ret = QMessageBox::question(this, tr("Speichern"), tr("Soll die aktuelle Datei gespeichert werden?"),
                                                                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (ret == QMessageBox::Yes) {
            saveFile();
        } else if (ret == QMessageBox::Cancel) {
            return;
        }
    }
    currentFile.clear();
    editor->clear();
    updatePreview();
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Markdown öffnen"), QString(), tr("Markdown-Dateien (*.md *.markdown);;Alle Dateien (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Fehler"), tr("Konnte Datei nicht öffnen: %1").arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    currentFile = fileName;
    editor->setPlainText(content);
    updatePreview();
}

bool MainWindow::saveToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Fehler"), tr("Konnte Datei nicht speichern: %1").arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();
    currentFile = filePath;
    return true;
}

void MainWindow::saveFile()
{
    if (currentFile.isEmpty()) {
        saveFileAs();
        return;
    }
    saveToFile(currentFile);
}

void MainWindow::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Speichern als"), QString(), tr("Markdown-Dateien (*.md);;Alle Dateien (*)"));
    if (fileName.isEmpty())
        return;
    saveToFile(fileName);
}

void MainWindow::updatePreview()
{
    // Qt6 has excellent markdown support
    QString md = editor->toPlainText();
    QTextDocument *doc = preview->document();
    
    // Qt6 setMarkdown is stable and feature-rich
    doc->setMarkdown(md);
    
    // Professional styling like GitHub/VSCode
    doc->setDefaultStyleSheet(
        // Body and general styling
        "body { "
        "  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', 'Noto Sans', Helvetica, Arial, sans-serif; "
        "  font-size: 16px; "
        "  line-height: 1.5; "
        "  color: #24292f; "
        "  background-color: #ffffff; "
        "  max-width: none; "
        "  padding: 20px; "
        "} "
        
        // Headers
        "h1, h2, h3, h4, h5, h6 { "
        "  margin-top: 24px; "
        "  margin-bottom: 16px; "
        "  font-weight: 600; "
        "  line-height: 1.25; "
        "  color: #1f2328; "
        "} "
        "h1 { "
        "  font-size: 2em; "
        "  border-bottom: 1px solid #d8dee4; "
        "  padding-bottom: 0.3em; "
        "} "
        "h2 { "
        "  font-size: 1.5em; "
        "  border-bottom: 1px solid #d8dee4; "
        "  padding-bottom: 0.3em; "
        "} "
        "h3 { font-size: 1.25em; } "
        "h4 { font-size: 1em; } "
        "h5 { font-size: 0.875em; } "
        "h6 { font-size: 0.85em; color: #656d76; } "
        
        // Paragraphs and text
        "p { "
        "  margin-top: 0; "
        "  margin-bottom: 16px; "
        "} "
        
        // Code styling
        "code { "
        "  font-family: 'SFMono-Regular', Consolas, 'Liberation Mono', Menlo, monospace; "
        "  font-size: 85%; "
        "  background-color: rgba(175, 184, 193, 0.2); "
        "  padding: 0.2em 0.4em; "
        "  border-radius: 6px; "
        "  color: #1f2328; "
        "} "
        
        // Code blocks
        "pre { "
        "  font-family: 'SFMono-Regular', Consolas, 'Liberation Mono', Menlo, monospace; "
        "  font-size: 85%; "
        "  background-color: #f6f8fa; "
        "  border: 1px solid #d0d7de; "
        "  border-radius: 6px; "
        "  padding: 16px; "
        "  overflow: auto; "
        "  margin-bottom: 16px; "
        "  color: #1f2328; "
        "} "
        "pre code { "
        "  background-color: transparent; "
        "  padding: 0; "
        "  border-radius: 0; "
        "} "
        
        // Lists
        "ul, ol { "
        "  margin-top: 0; "
        "  margin-bottom: 16px; "
        "  padding-left: 2em; "
        "} "
        "li { "
        "  margin-bottom: 0.25em; "
        "} "
        
        // Blockquotes
        "blockquote { "
        "  margin: 0 0 16px 0; "
        "  padding: 0 1em; "
        "  color: #656d76; "
        "  border-left: 0.25em solid #d8dee4; "
        "} "
        
        // Links
        "a { "
        "  color: #0969da; "
        "  text-decoration: none; "
        "} "
        "a:hover { "
        "  text-decoration: underline; "
        "} "
        
        // Tables
        "table { "
        "  border-collapse: collapse; "
        "  border-spacing: 0; "
        "  width: 100%; "
        "  margin-bottom: 16px; "
        "} "
        "th, td { "
        "  padding: 6px 13px; "
        "  border: 1px solid #d8dee4; "
        "} "
        "th { "
        "  background-color: #f6f8fa; "
        "  font-weight: 600; "
        "} "
        
        // Horizontal rule
        "hr { "
        "  border: none; "
        "  height: 0.25em; "
        "  background-color: #d8dee4; "
        "  margin: 24px 0; "
        "} "
        
        // Strong and emphasis
        "strong, b { "
        "  font-weight: 600; "
        "} "
        "em, i { "
        "  font-style: italic; "
        "} "
    );
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("Über mdedit"),
        tr("<h2>mdedit</h2>"
           "<p><b>Professioneller Markdown-Editor mit Live-Preview</b></p>"
           "<p>Version 1.1 - Mit Toolbar & Texteditor-Funktionen</p>"
           "<p>Entwickelt von: <b>Kemal Akçocuk</b></p>"
           "<p>Dies ist eine <b>Freeware</b> - kostenlos zur privaten und kommerziellen Nutzung.</p>"
           "<p>Erstellt mit Qt6 und C++</p>"
           "<hr>"
           "<p><small>© 2025 - Freie Software für alle</small></p>"));
}

// Text editor functions
void MainWindow::undoAction()
{
    editor->undo();
}

void MainWindow::redoAction()
{
    editor->redo();
}

void MainWindow::cutAction()
{
    editor->cut();
}

void MainWindow::copyAction()
{
    editor->copy();
}

void MainWindow::pasteAction()
{
    editor->paste();
}

void MainWindow::findAction()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Suchen"), 
                                              tr("Suchtext:"), QLineEdit::Normal, "", &ok);
    if (ok && !searchText.isEmpty()) {
        QTextCursor cursor = editor->textCursor();
        QTextDocument *document = editor->document();
        
        cursor = document->find(searchText, cursor);
        if (!cursor.isNull()) {
            editor->setTextCursor(cursor);
            editor->ensureCursorVisible();
        } else {
            QMessageBox::information(this, tr("Suchen"), tr("Text nicht gefunden."));
        }
    }
}

void MainWindow::replaceAction()
{
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Ersetzen"), 
                                              tr("Suchtext:"), QLineEdit::Normal, "", &ok);
    if (!ok || searchText.isEmpty()) return;
    
    QString replaceText = QInputDialog::getText(this, tr("Ersetzen"), 
                                               tr("Ersetzen durch:"), QLineEdit::Normal, "", &ok);
    if (!ok) return;
    
    QTextCursor cursor = editor->textCursor();
    QTextDocument *document = editor->document();
    
    cursor = document->find(searchText, cursor);
    if (!cursor.isNull()) {
        cursor.insertText(replaceText);
        editor->setTextCursor(cursor);
        
        QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Ersetzen"),
            tr("Weitersuchen und ersetzen?"), QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            replaceAction(); // Recursive call for next occurrence
        }
    } else {
        QMessageBox::information(this, tr("Ersetzen"), tr("Text nicht gefunden."));
    }
}

void MainWindow::zoomIn()
{
    currentFontSize += 1;
    QFont font = editor->font();
    font.setPointSize(currentFontSize);
    editor->setFont(font);
}

void MainWindow::zoomOut()
{
    if (currentFontSize > 8) {
        currentFontSize -= 1;
        QFont font = editor->font();
        font.setPointSize(currentFontSize);
        editor->setFont(font);
    }
}

void MainWindow::resetZoom()
{
    currentFontSize = 14;
    QFont font = editor->font();
    font.setPointSize(currentFontSize);
    editor->setFont(font);
}

void MainWindow::toggleWordWrap()
{
    if (editor->lineWrapMode() == QPlainTextEdit::WidgetWidth) {
        editor->setLineWrapMode(QPlainTextEdit::NoWrap);
    } else {
        editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    }
}
 