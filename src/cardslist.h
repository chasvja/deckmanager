#ifndef CARDSVIEW_H
#define CARDSVIEW_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QPoint>
#include <QFontMetrics>
#include <QSharedPointer>
#include <QApplication>
#include <QMimeData>
#include <QMouseEvent>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QWheelEvent>
#include <QtSql/QSqlQuery>
#include "card.h"
#include "carditem.h"
#include "deckview.h"
#include "typing.h"

class CardsList : public QWidget
{
    Q_OBJECT
protected:
    int itemAt(const QPoint &pos);

    QString adToString(int);
    virtual void startDrag(int);

    Type::Deck ls;
    QHash<quint32, CardItem> items;

    int pos;
    QSize cardSize;
    QPoint startPos;
    int cardsPerColumn;
    quint32 currentCardId;
    QScrollBar *sb;
    bool needRefreshId;
    QPoint point;
    int current;

public:
    explicit CardsList(QWidget *parent);
    ~CardsList();

    auto getList() -> decltype((ls))
    {
        return ls;
    }

    void paintEvent(QPaintEvent *);

    void wheelEvent(QWheelEvent *);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

    void setScrollBar(QScrollBar *);
    void setCurrentCardId(quint32 id)
    {
        currentCardId = id;
    }

    void refresh();

    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void sizeChanged(int);
    void currentIdChanged(quint32 id);
    void clickId(quint32);
    void details(quint32);
public slots:
    void setCards(Type::DeckP);
    void checkLeave();

private slots:
    void refreshCurrentId();
    void setPos(int _pos);
};

class CardsListView : public QWidget
{
    Q_OBJECT
private:
    CardsList *cl;
public:
    CardsListView(QWidget *parent);
    auto getList() -> decltype((cl->getList()))
    {
        return cl->getList();
    }

    void refresh()
    {
        cl->refresh();
    }

signals:
    void currentIdChanged(quint32 id);
    void clickId(quint32);
    void details(quint32);
public slots:

    void setCards(Type::DeckP cards)
    {
        cl->setCards(cards);
    }

    void setCurrentCardId(quint32 id)
    {
        cl->setCurrentCardId(id);
    }

    void checkLeave()
    {
        cl->checkLeave();
    }

private slots:
    void changeId(quint32 id)
    {
        emit currentIdChanged(id);
    }
};

#endif // CARDSVIEW_H
