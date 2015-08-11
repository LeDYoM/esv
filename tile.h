#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>

class Tile : public QObject
{
public:

    Tile(QObject *parent,QAbstractGraphicsShapeItem *graphItem, const QPoint point_, int sContent);
	virtual ~Tile();

	void setContent(int content_);
    int getContent() const { return content; }
    const QPoint &getPoint() const { return point; }
    QGraphicsItem *item() const { return _item; }

    void reSize(const QSizeF &tileSize);
private:
    QPoint point;
    int content;
    QAbstractGraphicsShapeItem *_item;
};

#endif // TILE_H
