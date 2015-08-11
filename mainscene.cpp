#include "mainscene.h"
#include "tile.h"
#include <QDebug>
#include <vector>
#include "boardmodel.h"
#include "boarddata.h"

MainScene::MainScene(const QRect &size, QObject *parent)
    :QGraphicsScene(size,parent),tiles{nullptr}
{
//    QObject::connect(this,MainScene::sceneRectChanged,this,MainScene::onSceneRectChanged);
}

MainScene::~MainScene()
{
    clear();
}

void MainScene::doBoardViewUpdate(const BoardModel *bModel)
{
    Q_ASSERT(bModel);
    int cont=0;

    if (!tiles)
    {
        tiles = new Matrix<Tile*>(bModel->size());
    }
    if (!tileSize.isValid())
    {
        tileSize = QSizeF(sceneRect().size().width() / tiles->size.width(),
                              sceneRect().size().height() / tiles->size.height());
    }

    for (int x=0;x<bModel->size().width();++x)
    {
        for (int y=0;y<bModel->size().height();++y)
        {
            QPoint point(x,y);
            const qint32 element = bModel->getElement(point);
            Tile *ftile = (*tiles)[x][y];
            if (!ftile)
            {
                if (!(cont%1000))
                    qDebug() << "Tile added: "<<cont;
                ++cont;
                auto rectItem = this->addRect(
                            QRectF(calculatePointForTile(point),tileSize));
                Tile *tile = new Tile(this,rectItem,point,element);
                (*tiles)[x][y] = tile;

//                addItem(rectItem);
//                tile->reSize(tileSize);
            }
            else
            {
                ftile->setContent(element);
            }
        }
    }
//    this->update();
}

void MainScene::resetCache()
{
    tileSize = QSizeF(-1,-1);
    if (tiles)
    {
        delete tiles;
        tiles = nullptr;
    }
    this->setItemIndexMethod(ItemIndexMethod::NoIndex);
    this->clear();
}

/*
void MainScene::onSceneRectChanged(const QRectF &rect)
{
    qDebug() << "Scene rect changed: "    <<rect;
    if (tiles)
    {

    }
}
*/

const QPointF MainScene::calculatePointForTile(const QPoint tilePoint)
{
    QPointF adv(tileSize.width()*(qreal)tilePoint.x(),tileSize.height()*(qreal)tilePoint.y());
    QPointF temp(sceneRect().topLeft()+adv);
    return temp;
}
