#ifndef MOVEFILTER_H
#define MOVEFILTER_H

#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QObject>
#include <QLabel>

class MoveEventFilter : public QObject
{    Q_OBJECT

public:
    MoveEventFilter(QWidget* parent = 0) : QObject(parent) {
        canMove = false;
    }
    bool canMove;

protected:
    bool eventFilter(QObject *obj, QEvent *event)
    {
        QMetaObject mo = QEvent::staticMetaObject;
        qDebug() << obj->objectName() << mo.enumerator(mo.indexOfEnumerator("Type")).valueToKey(event->type());

        if (event->type() == QEvent::MouseMove ){
            QMouseEvent* me = static_cast<QMouseEvent*>(event);
            qDebug() << QString("(%1|%2)").arg(me->pos().x()).arg(me->pos().y());
            return true;
        }

        return QObject::eventFilter(obj, event);
    }
};

class MouseTrack : public QLabel
{    Q_OBJECT
public:
    MouseTrack(QWidget* parent = 0) : QLabel(parent) {
    }
};

#endif // MOVEFILTER_H
