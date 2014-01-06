#include "tp_PropertyWidget.h"
#include <QHeaderView>

namespace tp {

  PropertyWidget::PropertyWidget(QWidget* parent):
    QTableWidget(parent),
    mObject(0)    
  {
  }

  void PropertyWidget::setObject(QObject* object) {
    clear();
    mObject=object;
    const QMetaObject* metaObject = object->metaObject();
    
    int nrProperties = metaObject->propertyCount();
    qDebug() << nrProperties;
    setRowCount(nrProperties-1);
    setColumnCount(2);
    int row = 0;
    for(int i = 0; i < nrProperties; i++) {
      QMetaProperty property = metaObject->property(i);
      const char* name = property.name();
      if(QString(name)==QString("objectName")) continue;
      QVariant value = object->property(name);
      setItem(row,0,new QTableWidgetItem(name));
      setItem(row,1,new QTableWidgetItem(value.toString()));
      item(row,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      item(row,1)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
      row++;
    }
    verticalHeader()->hide();
    horizontalHeader()->hide();

    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(writeProperty(QTableWidgetItem*)));
    
  }
}
