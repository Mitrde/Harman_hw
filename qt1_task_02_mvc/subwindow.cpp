#include "subwindow.h"
#include <QtWidgets>
#include <QAbstractItemView>


SubWindow::SubWindow()
    : m_model(new TreeModel),
      m_view(new QTreeView),
      m_fileName("test")
{
    updateWindowTitle();
    createView();
    m_delegate = new ComboDelegate(m_model);
    m_view->setItemDelegateForColumn(3, m_delegate);
}


SubWindow::~SubWindow()
{
    //delete m_delegate;
    emit aSubWindowClosed();
}

void SubWindow::newFileName()
{
    static int sequenceNumber = 1;

    //isUntitled = true;
    m_fileName = tr("document%1.db3").arg(sequenceNumber++);
    setWindowTitle(m_fileName + "[*]");    
    this->documentWasModified();
}

TreeModel* SubWindow::getModel() const { return m_model; }

QTreeView *SubWindow::getView() const
{
    return m_view;
}

void SubWindow::updateWindowTitle()
{
    if (m_fileName.size())
        setWindowTitle(m_fileName);
    else
        setWindowTitle("New Table");
}

bool SubWindow::loadFile(const QString &fileName)
{
    return m_model->setupModelData(fileName);
}

bool SubWindow::saveFile()
{
    if (isUntitled)
        return saveAs();
    else
        return save(m_fileName);
}

bool SubWindow::save(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);

    if (!m_model->setupSQLTableData(fileName))
    {
        errorMessage = tr("Cannot open file %1")
                       .arg(QDir::toNativeSeparators(fileName));
        return false;
    }
    QGuiApplication::restoreOverrideCursor();

    setFileName(fileName);
    return true;

}

bool SubWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), m_fileName);
    if (fileName.isEmpty())
        return false;
    return save(fileName);
}

void SubWindow::setFileName(QString fileName)
{
    int k = 0;
    k++;
    m_fileName = fileName;
    updateWindowTitle();
}

QString SubWindow::getFileName() const { return m_fileName; }

void SubWindow::documentWasModified()
{
    setWindowModified(true);
}

void SubWindow::insertChild()
{
    const QModelIndex index = m_view->selectionModel()->currentIndex();
        QAbstractItemModel *model = m_view->model();

        if (model->columnCount(index) == 0) {
            if (!model->insertColumn(0, index))
                return;
        }

        if (!model->insertRow(0, index))
            return;

        for (int column = 0; column < model->columnCount(index); ++column) {
            const QModelIndex child = model->index(0, column, index);
            model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
            if (!model->headerData(column, Qt::Horizontal).isValid())
                model->setHeaderData(column, Qt::Horizontal, QVariant(tr("[No header]")), Qt::EditRole);
        }

        m_view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                                  QItemSelectionModel::ClearAndSelect);
}

void SubWindow::insertRow()
{
    const QModelIndex index = m_view->selectionModel()->currentIndex();
        QAbstractItemModel *model = m_view->model();

        if (!model->insertRow(index.row()+1, index.parent()))
            return;

        for (int column = 0; column < model->columnCount(index.parent()); ++column) {
            const QModelIndex child = model->index(index.row() + 1, column, index.parent());
            model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
        }
}

void SubWindow::removeRow()
{
    const QModelIndex index = m_view->selectionModel()->currentIndex();
    QAbstractItemModel *model = m_view->model();
    model->removeRow(index.row(), index.parent());
}

void SubWindow::createView()
{
    m_view->setModel(m_model);    
    setCentralWidget(m_view);
}
