#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>

class Tile : public QGraphicsRectItem
{
public:

    Tile(QGraphicsItem *graphItemParent, const QRectF &rect, const QPoint point_, int sContent);
	virtual ~Tile();

	void setContent(int content_);
    int getContent() const { return content; }
    const QPoint &getPoint() const { return point; }
private:
    QPoint point;
    int content;
};

#endif // TILE_H
