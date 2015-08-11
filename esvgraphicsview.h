#ifndef ESVGRAPHICSWIDGET_H
#define ESVGRAPHICSWIDGET_H

#include <QGraphicsView>
#include <QRectF>
#include <QVector2D>

class ESVGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ESVGraphicsView(QWidget *parent = 0);
    virtual ~ESVGraphicsView();

    virtual void resizeEvent(QResizeEvent *rEvent) override;

    void updateZoom();
    void setZoom(const QVector2D &nv);

public Q_SLOTS:
    void adjustToWindowZoom();

private:
    QRectF lItemsBoundingBox;
    QRectF globalZoomedBoundingBox;
    QVector2D _zoom{1.0f,1.0f};
};

#endif // ESVGRAPHICSWIDGET_H
