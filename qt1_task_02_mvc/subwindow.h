#ifndef SUBWINDOW_H
#define SUBWINDOW_H


#include <QWidget>
#include <QTreeView>
#include <QMainWindow>
#include "treemodel.h"
#include "combodelegate.h"

class SubWindow : public QMainWindow
{
    Q_OBJECT

public:
    SubWindow();    
    ~SubWindow();

    void newFileName();

    TreeModel* getModel() const;
    QTreeView* getView() const;

    void updateWindowTitle();

    bool loadFile(const QString &fileName);
    bool saveFile();
    bool save(const QString &fileName);
    bool saveAs();

    void setFileName(QString fileName);
    QString getFileName() const;
public slots:
    void insertChild();
    //bool insertColumn();
    void insertRow();
    //bool removeColumn();
    void removeRow();
private slots:
    void documentWasModified();



private:
    TreeModel* m_model;
    QTreeView* m_view;

    ComboDelegate* m_delegate;
    bool isUntitled;
    QString m_fileName;



    void createView();

signals:
    void aSubWindowClosed();
};
#endif // SUBWINDOW_H
