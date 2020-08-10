#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMdiArea>
#include <QTreeView>
#include <QArrayData>

#include "treemodel.h"
#include "subwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void addToRecentFileList(QString t_fileName);
    void updateRecentFileList();

    void loadTreeFromFile(QString t_fileName);

    SubWindow* createSubWindow();
    SubWindow* activeSubWindow() const;


    Ui::MainWindow *m_ui;

    QVector<TreeModel*> m_vpModels;
    QVector<SubWindow*> m_vpWindows;

    SubWindow* m_activeWindow;

    QStringList m_recentFiles;
    std::array<QAction*, 5> m_aActions;

public slots:
    void updateActions();

private slots:
    void sFileNew();
    void sFileOpen();
    void sFileOpenRecent();
    void sFileSave();
    void sFileSaveAs();
    void sAbout();
    //void sFileSaveAll();

    void sCloseAllSubWindows();

    void sAdd_directory();
    void sAdd_subdirectory();
    void sRemove_directory();

    void sSetActiveWindow(QMdiSubWindow* t_mdiSubWindow);

    void sMenuBarLocker();
    void sMenuBarUnlocker();

signals:
    void hasActiveWindow();
    void noActiveWindow();

};
#endif // MAINWINDOW_H
