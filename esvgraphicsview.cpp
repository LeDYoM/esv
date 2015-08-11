#include "esvgraphicsview.h"
#include <QDebug>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGLWidget>

ESVGraphicsView::ESVGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    QGLWidget *mw = new QGLWidget();
//    mw->setAutoFillBackground(false);
    mw->setAcceptDrops(false);
    setViewport(mw);
}

ESVGraphicsView::~ESVGraphicsView()
{

}

void ESVGraphicsView::resizeEvent(QResizeEvent *rEvent)
{
    Q_UNUSED(rEvent);
    adjustToWindowZoom();
}

void ESVGraphicsView::adjustToWindowZoom()
{
    if (scene())
    {
        lItemsBoundingBox = scene()->itemsBoundingRect();
        updateZoom();
        qDebug() << "Current zoom: "<<_zoom;
        qDebug() << "GlobalZoomedBoundBox: "<<globalZoomedBoundingBox;
        fitInView(globalZoomedBoundingBox, Qt::IgnoreAspectRatio);
        qDebug() << "Viewport: " << viewport()->rect();
    }
}

QRectF doZoom(const QRectF &rect,const QVector2D &v,const QPointF &center)
{
    QSizeF hSize = QSizeF(rect.width()/2.0f,rect.height()/2.0f);
    QSizeF zhSize = QSizeF(hSize.width()*v.x(),hSize.height()*v.y());
    QSizeF zSize = QSizeF(rect.width()*v.x(),rect.height()*v.y());
    QRectF result(center.x()-zhSize.width(),center.y()-zhSize.height(),
                  zSize.width(),zSize.height());
    return result;
}

void ESVGraphicsView::updateZoom()
{
    globalZoomedBoundingBox = doZoom(lItemsBoundingBox,_zoom,lItemsBoundingBox.center());
}

void ESVGraphicsView::setZoom(const QVector2D &nv)
{
    if (_zoom!=nv)
    {
        _zoom = nv;
        adjustToWindowZoom();
    }
}

