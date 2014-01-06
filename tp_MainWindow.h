#ifndef __TP__MAIN_WINDOW_H__
#define __TP__MAIN_WINDOW_H__

#include <QtCore>
#include <QtGui>
#include <QMainWindow.h>
#include <QTreeView>
#include "tp_GraphicsWidget.h"
#include "tp_GraphicsTreeModel.h"
#include "tp_GraphicsItem.h"

namespace tp {
  
  class MainWindow: public QMainWindow {
    Q_OBJECT 
  public:
    explicit MainWindow();

  private slots:
      void addItem();
      void removeItem();
      void propertyChanged(QObject*);

  signals:
      void propertyChanged();
  private:
    void setupModel();
  private:
    GraphicsWidget*     mGraphicsWidget;
    GraphicsTreeModel*  mTreeModel;
    QTreeView*          mTreeView;

  };
  
}

#endif
