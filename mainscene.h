#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "boardmodel.h"
#include <QGraphicsScene>
#include "boarddata.h"

class Tile;

class MainScene : public QGraphicsScene
{
	Q_OBJECT

public:
    MainScene(const QRect &, QObject *parent=nullptr);
    Q_DISABLE_COPY(MainScene)
	virtual ~MainScene();

    void doBoardViewUpdate(const BoardModel *bModel);
    void resetCache();

//private Q_SLOTS:
//    void onSceneRectChanged(const QRectF &rect);
private:
    QSizeF tileSize;
    Matrix<Tile*> *tiles;
    const QPointF calculatePointForTile(const QPoint tilePoint);
};

#endif // MAINSCENE_H
