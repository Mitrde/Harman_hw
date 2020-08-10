#include <QtWidgets>
#include <QStringListModel>
#include <QTableView>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
{
    m_ui->mdiArea = new QMdiArea;
    m_ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_ui->setupUi(this);


    m_aActions = { m_ui->actionRecentFile0, m_ui->actionRecentFile1, m_ui->actionRecentFile2, m_ui->actionRecentFile3, m_ui->actionRecentFile4 };
    QFile t_file("recent_files.txt");
    if (t_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&t_file);
        QString t_string = t_file.readLine();
        for (int i = 0; i < 5 && i < t_string.split(';').size() - 1; ++i)
            m_recentFiles.push_back(t_string.split(';').at(i));
    }
    updateRecentFileList();

    connect(m_ui->actionNew, &QAction::triggered, this, &MainWindow::sFileNew);
    connect(m_ui->actionOpen, &QAction::triggered, this, &MainWindow::sFileOpen);
    connect(m_ui->actionSave, &QAction::triggered, this, &MainWindow::sFileSave);
    connect(m_ui->actionSave_as, &QAction::triggered, this, &MainWindow::sFileSaveAs);
    //connect(m_ui->actionSaveAll, &QAction::triggered, this, &MainWindow::sFileSaveAll);
    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(m_ui->actionClose_All, &QAction::triggered, this, &MainWindow::sCloseAllSubWindows);
    //
    connect(m_ui->actionAdd_directory, &QAction::triggered, this, &MainWindow::sAdd_directory);

    connect(m_ui->actionAdd_subdirectory, &QAction::triggered, this, &MainWindow::sAdd_subdirectory);

    connect(m_ui->actionRemove_directory, &QAction::triggered, this, &MainWindow::sRemove_directory);

    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::sAbout);
    connect(m_ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::sSetActiveWindow);

    connect(this, &MainWindow::hasActiveWindow, this, &MainWindow::sMenuBarUnlocker);
    connect(this, &MainWindow::noActiveWindow, this, &MainWindow::sMenuBarLocker);
    for (size_t i = 0; i < 5; ++i)
        connect(m_aActions.at(i), &QAction::triggered, this, &MainWindow::sFileOpenRecent);

}

MainWindow::~MainWindow()
{
    delete m_ui->mdiArea;
    delete m_ui;
}
SubWindow *MainWindow::createSubWindow()
{
    SubWindow *window = new SubWindow();
    m_ui->mdiArea->addSubWindow(window);

    return window;
}

void MainWindow::addToRecentFileList(QString fileName)
{
    if (!m_recentFiles.contains(fileName))
    {
        if (m_recentFiles.size() == 5)
            m_recentFiles.pop_front();
        m_recentFiles.push_back(fileName);
        updateRecentFileList();
    }
}

void MainWindow::updateRecentFileList()
{
    m_aActions.at(0)->setText("(none)");
    m_aActions.at(0)->setData("");
    m_aActions.at(0)->setEnabled(false);
    for (size_t i = 1; i < 5; ++i)
    {
        m_aActions.at(i)->setEnabled(false);
        m_aActions.at(i)->setVisible(false);
    }

    for (int i = 0; i < m_recentFiles.size(); ++i)
    {
        m_aActions.at(i)->setText(m_recentFiles[i]);
        m_aActions.at(i)->setData(m_recentFiles[i]);
        m_aActions.at(i)->setEnabled(true);
        m_aActions.at(i)->setVisible(true);
    }

    if (m_recentFiles.size())
    {
        QFile t_file("recent_files.txt");
        if (t_file.open(QIODevice::WriteOnly | QIODevice::Text))
            for (int i = 0; i < m_recentFiles.size(); ++i)
                QTextStream(&t_file) << m_recentFiles[i].toUtf8() + ';';
    }
}

void MainWindow::loadTreeFromFile(QString fileName)
{
    SubWindow *window = createSubWindow();
    window->setFileName(fileName);
    const bool succeeded = window->loadFile(fileName);

    if (succeeded)
        window->show();
    else
        window->close();

    addToRecentFileList(fileName);
}



void MainWindow::sFileNew()
{
    SubWindow *window = createSubWindow();
    window->newFileName();
    window->showMaximized();
}

void MainWindow::sFileOpen()
{
    QString t_fileName = QFileDialog::getOpenFileName();
    loadTreeFromFile(t_fileName);
    addToRecentFileList(t_fileName);
}

void MainWindow::sFileOpenRecent()
{
    QAction *t_pAction = qobject_cast<QAction*>(sender());
    if (t_pAction)
    {
        QString t_fileName = t_pAction->data().toString();
        loadTreeFromFile(t_fileName);
    }
}

void MainWindow::sFileSave()
{
    if (m_activeWindow->saveFile())
        statusBar()->showMessage(tr("File saved"), 2000);
    addToRecentFileList(m_activeWindow->getFileName());
}

void MainWindow::sFileSaveAs()
{
    if (m_activeWindow->saveAs())
        statusBar()->showMessage(tr("File saved"), 2000);
    addToRecentFileList(m_activeWindow->getFileName());
}

void MainWindow::sCloseAllSubWindows()
{
    m_ui->mdiArea->closeAllSubWindows();
}

void MainWindow::sAdd_directory()
{
    if (m_activeWindow)
    {
        m_activeWindow->insertRow();
        updateActions();
    }

}

void MainWindow::sAdd_subdirectory()
{
    if (m_activeWindow)
    {
        m_activeWindow->insertChild();
        updateActions();
    }
}

void MainWindow::sRemove_directory()
{
    if (m_activeWindow)
    {
        m_activeWindow->removeRow();
        updateActions();
    }
}



void MainWindow::sSetActiveWindow(QMdiSubWindow* t_mdiSubWindow)
{
    if (t_mdiSubWindow)
    {
        m_activeWindow = qobject_cast<SubWindow*>(t_mdiSubWindow->widget());
        emit hasActiveWindow();
    }
    else
    {
        emit noActiveWindow();
    }
}
void MainWindow::sAbout()
{
    QMessageBox::about(this, tr("About the programm"),
                       tr("The editor of the record tree stored in the SQLite relational table " ));
}
void MainWindow::updateActions()
{
    //const bool hasSelection = !m_activeWindow->getView()->selectionModel()->selection().isEmpty();
    //const bool hasCurrent = m_activeWindow->getView()->selectionModel()->currentIndex().isValid();
    //m_ui->actionAdd_directory->setEnabled(hasCurrent);
    //m_ui->actionAdd_subdirectory->setEnabled(hasCurrent);
    //m_ui->actionRemove_directory->setEnabled(hasSelection);
}

void MainWindow::sMenuBarLocker()
{
    m_ui->actionSave->setEnabled(false);
    m_ui->actionSave_as->setEnabled(false);
}

void MainWindow::sMenuBarUnlocker()
{
    m_ui->actionSave->setEnabled(true);
    m_ui->actionSave_as->setEnabled(true);
}

