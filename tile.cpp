#include "tile.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QBrush>

Tile::Tile(QObject *parent,QAbstractGraphicsShapeItem *graphItem, const QPoint point_, int sContent)
    : QObject{parent},point{point_},content{sContent}, _item{graphItem}
{
    setContent(sContent);
}

Tile::~Tile()
{
}

void Tile::setContent(int content_)
{
    content = content_;
    _item->setPen(QPen(Qt::NoPen));
    if (content!=0)
    {
        _item->setBrush(QBrush(Qt::red));
    }
    else
    {
        _item->setBrush(QBrush(Qt::yellow));
    }
}

void Tile::reSize(const QSizeF &tileSize)
{
    QPointF adv(tileSize.width()*(qreal)point.x(),tileSize.height()*(qreal)point.y());
    auto scn = _item->scene();
    auto scnRect = scn->sceneRect();
    QPointF temp(scnRect.topLeft()+adv);
}
