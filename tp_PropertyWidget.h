#ifndef __TP_PROPERTY_WIDGET__
#define __TP_PROPERTY_WIDGET__

#include <QtCore>
#include <QTableWidget>

namespace tp {

  class PropertyWidget: public QTableWidget {
    Q_OBJECT
  public:
    PropertyWidget(QWidget* parent=0);
    
    void setObject(QObject* object);

 public slots:
    void selected(const QModelIndex& index) {
      setObject(static_cast<QObject*>(index.internalPointer()));
    }

  signals:
    void propertyChanged(QObject*);

private slots:
   void writeProperty(QTableWidgetItem* onItem) {
     QString  name  = item(onItem->row(),0)->text();
     QVariant value = onItem->text();
     mObject->setProperty(name.toStdString().c_str(),value);
     emit(propertyChanged(mObject));

   }
    

  private:
    QObject* mObject;
  };

}

#endif
