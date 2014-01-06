#ifndef __TP_GRAPHICS_TREE_MODEL_H__
#define __TP_GRAPHICS_TREE_MODEL_H__

#include <QtCore>
#include <QAbstractItemModel>
#include "tp_GraphicsItem.h"

namespace tp {

class GraphicsTreeModel: public QAbstractItemModel {
    Q_OBJECT
public:
    GraphicsTreeModel(QObject* parent=0):
        QAbstractItemModel(parent) {
        mRoot = new GraphicsItem("Origin");
    }
    ~GraphicsTreeModel() {
        delete mRoot;
    }

    int nrChildren() const { 
      return mRoot->nrChildren();
    }

    QVariant data(const QModelIndex& index, int role) const {
        if(!index.isValid())
            return QVariant();
        if(role != Qt::DisplayRole)
            return QVariant();

        GraphicsItem* item = static_cast<GraphicsItem*>(index.internalPointer());
        return item->data(index.column());
    }

    QModelIndex parent(const QModelIndex& index) const{
        if(!index.isValid())
            return QModelIndex();
        GraphicsItem* childItem = static_cast<GraphicsItem*>(index.internalPointer());
        GraphicsItem* parentItem = childItem->parent();
        if(parentItem == mRoot)
            return QModelIndex();
        return createIndex(parentItem->row(),0,parentItem);
    }

    int rowCount(const QModelIndex& parent=QModelIndex()) const {
        GraphicsItem* parentItem;
        if(parent.column() > 0)
            return 0;
        if(!parent.isValid())
            parentItem = mRoot;
        else
            parentItem = static_cast<GraphicsItem*>(parent.internalPointer());
        return parentItem->childCount();
    }

    int columnCount(const QModelIndex& parent=QModelIndex()) const {
        if(parent.isValid())
            return static_cast<GraphicsItem*>(parent.internalPointer())->columnCount();
        else
            return mRoot->columnCount();
    }

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const {
        if(!hasIndex(row,column,parent))
            return QModelIndex();

        GraphicsItem* parentItem;
        if(!parent.isValid())
            parentItem = mRoot;
        else
            parentItem = static_cast<GraphicsItem*>(parent.internalPointer());

        GraphicsItem* childItem = parentItem->child(row);
        if(childItem)
            return createIndex(row,column,childItem);
        else
            return QModelIndex();

    }
    Qt::ItemFlags flags(const QModelIndex& index) const {
        if(!index.isValid())
            return 0;
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    }

    GraphicsItem* getItem(const QModelIndex& index) const {
      if (index.isValid()) {
	GraphicsItem* item = static_cast<GraphicsItem*>(index.internalPointer());
	if (item) return item;
     }
      return mRoot;
    }

    bool insertRows(int position, int rows, const QModelIndex &parent)
    {
      GraphicsItem *parentItem = getItem(parent);
      bool success;
      beginInsertRows(parent, position, position + rows - 1);
      success = parentItem->insertChildren(position, rows, 0);
      endInsertRows();
     
     return success;
    }

    bool removeRows(int from, int to, const QModelIndex& parent) {
      beginRemoveRows(parent,from,to);
      GraphicsItem* item = getItem(parent);
      bool results = item->removeChildren(from,to);
      endRemoveRows();
      return results;

    }
      
    GraphicsItem* getRoot() const { return mRoot; }
private:
    GraphicsItem* mRoot;

};

}

#endif
