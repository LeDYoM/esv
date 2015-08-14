#include "tile.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QBrush>

Tile::Tile(QGraphicsItem *graphItemParent, const QRectF &rect, const QPoint point_, int sContent)
    : QGraphicsRectItem{rect,graphItemParent},point{point_},content{sContent}
{
    setContent(sContent);
}

Tile::~Tile()
{
}

void Tile::setContent(int content_)
{
    content = content_;
    setPen(QPen(Qt::NoPen));
    if (content!=0)
    {
        setBrush(QBrush(Qt::red));
    }
    else
    {
        setBrush(QBrush(Qt::yellow));
    }
}
