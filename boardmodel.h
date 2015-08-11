#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QObject>
#include <QSize>
#include <QVector>
#include <QPoint>
#include "boarddata.h"

class NewBoardOptions;

class BoardModel : public QObject
{
	Q_OBJECT

    Q_PROPERTY (QSize size READ size FINAL)
    Q_PROPERTY (int area READ area STORED false FINAL)

public:
    explicit BoardModel(const NewBoardOptions *nbo, QObject *parent=nullptr);

    BoardModel &operator=(const BoardModel &other);
    virtual ~BoardModel();

    bool operator==(const BoardModel &other) const;

    qint32 getElement(const QPoint &point) const;
    qint32 getElement(const QPoint &point);
    Q_INVOKABLE void setFutureElement(const QPoint &point, qint32 fElement);
    Q_INVOKABLE int countNeighbours(const QPoint &point) const;
    Q_INVOKABLE bool elementIsEmpty(const QPoint &point) const;
    Q_INVOKABLE bool elementIsOccupied(const QPoint &point) const;
    Q_INVOKABLE void occupyFutureElement(const QPoint &point);
    Q_INVOKABLE void freeFutureElement(const QPoint &point);
    Q_INVOKABLE void forwardFutureElement(const QPoint &point);

    void setElement(const QPoint &point, const qint32 nElement);
    void setBoardData(const BoardData &data_);

    void makeFutureCurrent(BoardModel *const bmOut=nullptr);

    // Properties

    // Getters
    QSize size() const;
    int area() const { return size().width() * size().height(); }

private:
    explicit BoardModel(const BoardModel &other);

    QPoint toModelOptions(const QPoint &point) const;

    const BoardData &getBoardData() const { return boardData; }
    BoardData &getBoardData() { return boardData; }

    BoardData boardData;
    BoardData *futureBoardData;
    friend class BoardModelCollection;
    friend class FileManager;
};

Q_DECLARE_METATYPE(BoardModel*)

#endif // BOARDMODEL_H
