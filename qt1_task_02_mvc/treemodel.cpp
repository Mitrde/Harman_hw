#include "treemodel.h"
#include "treeitem.h"

#include <QtWidgets>
#include <QtWidgets/QApplication>


TreeModel::TreeModel(const QString &path, QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    m_enum = {"One", "Two", "Three", "Four"};
    rootData << "String"<<"Int"<<"Bool"<<"Enum";
    dbase = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    qDebug()  <<  QSqlDatabase::drivers();

    rootItem = new TreeItem(rootData);
    setupModelData(path);
}

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    m_enum = {"One", "Two", "Three", "Four"};
    rootData << "String"<<"Int"<<"Bool"<<"Enum";

    dbase = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    qDebug()  <<  QSqlDatabase::drivers();

    rootItem = new TreeItem(rootData);

    //setupModelData("new_document"); //?????????
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return rootItem->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);


    if (index.column() == 3 && role == Qt::DisplayRole)
        return item->data(index.column()) < 0 ? "" : m_enum[item->data(index.column()).toInt()];


    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        switch (section)
        {
        case 0:
            return "string";
        case 1:
            return "integer";
        case 2:
            return "boolean";
        case 3:
            return "enumeration";
        }

    return QAbstractItemModel::headerData(section, orientation, role);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    const bool success = rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    const bool success = rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

QVector<QString> TreeModel::getEnumeration() const
{
    return m_enum;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    const TreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem->childCount() : 0;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

bool TreeModel::setupSQLTableData(const QString &dbName)
{
    QList <TreeItem*> queue;
    QList <int> parents_queue;
    int i = 0;
    QSqlQuery *a_query;

    queue.push_back(rootItem);
    parents_queue.push_back(0);
    if(!dbase.isOpen())
    {
        dbase.setDatabaseName(dbName);
        if (!dbase.open())
        {
            qDebug() << "DB IS NOT OPENED";
            return false;
        }
        if(dbase.isOpen())
            qDebug() << "DBASE IS OPENED";
    }
    else
        qDebug() << "dbase is opened";



    a_query=new QSqlQuery(dbase);
    // DDL query
    QString str = "DROP TABLE IF EXISTS my_table;";


    if (! a_query->exec(str)) {
        qDebug() << "Can't drop sqlite table, chmo";
    }
    else
         qDebug() << "Sqlite table is clear or not exist";




    str = "CREATE TABLE my_table ("
                  "id integer PRIMARY KEY NOT NULL, "
                  "p_id integer,"
                  "String TEXT, "
                  "Integer integer,"
                  "Boolean integer DEFAULT 0,"
                  "Enumeration integer"
                  ")WITHOUT ROWID;";
    bool b = a_query->exec(str);
    if (!b) {
        qDebug() << "Can't create sqlite table, check your pockets";
    }    


    while(queue.size() != 0)
    {
        TreeItem* current = queue.first();
        int p_id = parents_queue.first();
        QString str_insert = "INSERT INTO my_table(id, p_id, String, Integer, Boolean, Enumeration) "
                "VALUES (%1, %2, '%3', %4, %5, %6);";
        str = str_insert.arg(i)
                .arg(p_id)
                .arg(current->data(0).toString())
                .arg(current->data(1).toInt())
                .arg(current->data(2).toInt())
                .arg(current->data(3).toInt());
        b = a_query->exec(str);
        if (!b) { qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";}

        for (int it = 0; it< current->childCount(); ++it)
        {
            queue.push_back(current->child(it));
            parents_queue.push_back(i);

        }
        qDebug()<< "child inserted to db";

        queue.pop_front();
        parents_queue.pop_front();
        ++i;
    }
    dbase.close();
    return true;
}



bool TreeModel::setupModelData(const QString &dbName)
{
    QSqlQuery *a_query;
    if(!dbase.isOpen())
    {
        dbase.setDatabaseName(dbName);
        if (!dbase.open())
        {
            qDebug() << "DB IS NOT OPENED";
            return false;
        }
        if(dbase.isOpen())
            qDebug() << "DBASE IS OPENED";
    }
    else
        qDebug() << "dbase is opened";

    a_query=new QSqlQuery(dbase);
    QString str = "SELECT * FROM my_table";
    if (!a_query->exec(str))
    {
        qDebug() << "Даже селект не получается, я пас.";
        return false;
    }
    else
    {
        qDebug() << "SELECT SUCCEED";
    }

    QSqlRecord rec = a_query->record();


    QVector<TreeItem*> parents;
    parents << rootItem;
    a_query->next();


    while(a_query->next())
    {
        //qDebug() << a_query->value(rec.indexOf("String")).toString();
        QVector<QVariant> columnData;
        columnData.push_back( a_query->value(rec.indexOf("String")).toString());
        //qDebug() << a_query->value(rec.indexOf("String")).toString();
        columnData.push_back( a_query->value(rec.indexOf("Integer")).toInt());
        columnData.push_back( a_query->value(rec.indexOf("Boolean")).toBool());
        columnData.push_back( a_query->value(rec.indexOf("Enumeration")).toInt());
        int p_id = a_query->value(rec.indexOf("p_id")).toInt();

        TreeItem *parent = parents[p_id];

        parent->insertChildren(parent->childCount(), 1, rootItem->columnCount());
        for (int column = 0; column < columnData.size(); ++column)
            parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        parents << parent->child(parent->childCount() - 1);
    }

    dbase.close();
    return true;
}
