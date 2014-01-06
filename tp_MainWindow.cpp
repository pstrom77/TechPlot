#include "tp_MainWindow.h"
#include <QDockWidget>
#include "tp_GraphicsTreeModel.h"
#include "tp_GraphicsItem.h"
#include "tp_PropertyWidget.h"

namespace tp {


  MainWindow::MainWindow() {

    mGraphicsWidget = new GraphicsWidget(this);
    setCentralWidget(mGraphicsWidget);

    mTreeModel = new GraphicsTreeModel(this);
    setupModel();

    mTreeView = new QTreeView(this);
    mTreeView->header()->setVisible(false);
    mTreeView->setModel(mTreeModel);

    mGraphicsWidget->setModel(mTreeModel);

    QWidget* mControlWidget = new QWidget(this);
    mControlWidget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum,QSizePolicy::Minimum));
    QVBoxLayout* tLayout = new QVBoxLayout();
    mControlWidget->setLayout(tLayout);
    tLayout->addWidget(mTreeView);
    
    QPushButton* mAddButton = new QPushButton("Add");
    QPushButton* mRemoveButton = new QPushButton("Remove");
    QHBoxLayout* tLayout2 = new QHBoxLayout();
    tLayout2->addWidget(mAddButton);
    tLayout2->addWidget(mRemoveButton);
    tLayout2->addStretch(1);
    tLayout->addLayout(tLayout2);
    
    connect(mAddButton,SIGNAL(clicked()), this, SLOT(addItem()));
    connect(mRemoveButton,SIGNAL(clicked()), this, SLOT(removeItem()));


    QDockWidget* dockWidget = new QDockWidget(tr("Tree"),this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidget->setWidget(mControlWidget);
    addDockWidget(Qt::LeftDockWidgetArea,dockWidget);
    
    PropertyWidget* mPropertyWidget = new PropertyWidget();
    mPropertyWidget->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum));

    QDockWidget* dockWidget2 = new QDockWidget(tr("Properties"),this);
    dockWidget2->setAllowedAreas(Qt::RightDockWidgetArea);;
    dockWidget2->setWidget(mPropertyWidget);
    addDockWidget(Qt::RightDockWidgetArea,dockWidget2);


    mPropertyWidget->setObject(mTreeModel->getRoot());    
    connect(mTreeView,SIGNAL(clicked(const QModelIndex&)), mPropertyWidget, SLOT(selected(const QModelIndex&)));
    connect(mPropertyWidget,SIGNAL(propertyChanged(QObject*)), this,SLOT(propertyChanged(QObject*)));
    connect(this,SIGNAL(propertyChanged()), mGraphicsWidget,SLOT(update()));
    connect(this,SIGNAL(propertyChanged()), mTreeView,SLOT(update()));

    statusBar()->showMessage(tr("Nr items: %1").arg(mTreeModel->nrChildren()));

  }
  
  
  void MainWindow::setupModel() {

      GraphicsItem* item2 = new GraphicsItem("Root X", mTreeModel->getRoot());
      item2->setTranslate(QVector3D(10,0,0));
      item2->setPen(QPen(Qt::black));
      item2->setLineWidth(2.0);

      GraphicsItem* item3 = new GraphicsItem("Root Y", mTreeModel->getRoot());
      item3->setTranslate(QVector3D(0,10,0));
      item3->setPen(QPen(Qt::black));
      item3->setLineWidth(2.0);

      GraphicsItem* item4 = new GraphicsItem("Root Z", mTreeModel->getRoot());
      item4->setTranslate(QVector3D(0,0,10));
      item4->setPen(QPen(Qt::black));
      item4->setLineWidth(2.0);


      GraphicsItem* parent = item2;
      for(int i = 0; i < 23;i++) {
        GraphicsItem* item= new GraphicsItem(QString("Child %1").arg(i),parent);
        item->setTranslate(QVector3D(0,0,5));
        item->setRotationX(15);
        item->setPen(QPen(Qt::red));
        parent = item;
      }

      parent = item3;
      for(int i = 0; i < 23;i++) {
        GraphicsItem* item= new GraphicsItem(QString("Child %1").arg(i),parent);
        item->setTranslate(QVector3D(5,0,0));
        item->setRotationY(15);
        item->setPen(QPen(Qt::green));
        parent = item;
      }

      parent = item4;
      for(int i = 0; i < 23;i++) {
        GraphicsItem* item= new GraphicsItem(QString("Child %1").arg(i),parent);
        item->setTranslate(QVector3D(0,5,0));
        item->setRotationZ(15);
        item->setPen(QPen(Qt::blue));
        parent = item;
      }

  }


  void MainWindow::addItem() {
    qDebug() << "# Items before add: " << mTreeModel->nrChildren();
    QModelIndex index = mTreeView->selectionModel()->currentIndex();
    mTreeModel->insertRows(index.row(),1, index);
    qDebug() << "# Items after add: " << mTreeModel->nrChildren();
    statusBar()->showMessage(tr("Nr items: %1").arg(mTreeModel->nrChildren()));
    mGraphicsWidget->update();
  }

  void MainWindow::removeItem() {
    qDebug() << "# Items before remove: " << mTreeModel->nrChildren();
    QModelIndex index = mTreeView->selectionModel()->currentIndex();
    QAbstractItemModel* model = mTreeView->model();
    model->removeRows(index.row(),index.row()+1,index.parent());
    qDebug() << "# Items after remove: " << mTreeModel->nrChildren();
    statusBar()->showMessage(tr("Nr items: %1").arg(mTreeModel->nrChildren()));
    mGraphicsWidget->update();
  }

  void MainWindow::propertyChanged(QObject*) {
    emit(propertyChanged());
    QModelIndex index = mTreeView->selectionModel()->currentIndex();
    mTreeView->dataChanged(index,index);
  }
}
