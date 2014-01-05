#include "tp_MainWindow.h"
#include <QDockWidget>
#include "tp_GraphicsItem.h"

namespace tp {


  MainWindow::MainWindow() {

    mGraphicsWidget = new GraphicsWidget(this);
    setCentralWidget(mGraphicsWidget);

    mTree = new QTreeWidget(this);
    mTree->setColumnCount(1);    
    
    mGraphicsWidget->setTree(mTree);

    
    QDockWidget* dockWidget = new QDockWidget(tr("Tree"),this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidget->setWidget(mTree);
    addDockWidget(Qt::LeftDockWidgetArea,dockWidget);
    
    
    GraphicsItem* item1  = addRoot("Root 1");
    GraphicsItem* item2 = addRoot("Root 2");
    item2->translate(QVector3D(10,0,0));
    item2->rotateX(0);
    item2->rotateY(45*DEGTORAD);
    item2->rotateZ(45*DEGTORAD);
    
    
  }
  
  
  
  GraphicsItem*  MainWindow::addRoot(QString name) {
    GraphicsItem* item = new GraphicsItem(mTree);
    item->setText(0,name);
    item->setGraphicsWidget(mGraphicsWidget);
    mTree->addTopLevelItem(item); 
    return item;  
  }
  
  GraphicsItem* MainWindow::addChild(QTreeWidgetItem* parent, QString name ) {
    GraphicsItem* item = new GraphicsItem(parent);
    item->setText(0,name);
    parent->addChild(item);
    return item;
  }

}
