#ifndef __TP__MAIN_WINDOW_H__
#define __TP__MAIN_WINDOW_H__

#include <QtCore>
#include <QtGui>
#include <QMainWindow.h>
#include <QTreeWidget>
#include "tp_GraphicsWidget.h"
#include "tp_GraphicsItem.h"

namespace tp {
  
  class MainWindow: public QMainWindow {
    Q_OBJECT 
  public:
    explicit MainWindow();

    GraphicsItem* addRoot(QString name);
    GraphicsItem* addChild(QTreeWidgetItem* parent, QString name);
  private:
    GraphicsWidget* mGraphicsWidget;
    QTreeWidget*  mTree;

  };
  
}

#endif
