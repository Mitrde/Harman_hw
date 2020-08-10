#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVector>
#include <QVariant>

struct Data
{
    QString m_strName;
    int m_nValue;
    bool m_bEnabled;
    int m_nVariant;
    Data(const QString &rcName = QString(), int nValue = 0, bool bEnabled = false, int nVariant = 0)
        : m_strName(rcName)
        , m_nValue(nValue)
        , m_bEnabled(bEnabled)
        , m_nVariant(nVariant)
    {}
};

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();

    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    QVector<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem *parentItem;
};

#endif // TREEITEM_H
