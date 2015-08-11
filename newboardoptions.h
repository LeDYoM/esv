#ifndef NEWBOARDOPTIONS_H
#define NEWBOARDOPTIONS_H

#include <QObject>
#include <QSize>

class NewBoardOptions : public QObject
{
    Q_OBJECT

    Q_PROPERTY (int newBoardWidth READ newBoardWidth WRITE setNewBoardWidth FINAL)
    Q_PROPERTY (int newBoardHeight READ newBoardHeight WRITE setNewBoardHeight FINAL)
    Q_PROPERTY (QSize newBoardSize READ newBoardSize STORED false FINAL)
    Q_PROPERTY (bool loopBoard READ loopBoard FINAL)

public:
    explicit NewBoardOptions(QObject *parent = 0):QObject{parent} {}
    ~NewBoardOptions() {}

    int newBoardWidth() const { return _newBoardWidth; }
    void setNewBoardWidth(int nv) { _newBoardWidth = nv; }
    int newBoardHeight() const { return _newBoardHeight; }
    void setNewBoardHeight(int nv) { _newBoardHeight = nv; }

    QSize newBoardSize() const { return QSize(_newBoardWidth,_newBoardHeight); }

    bool loopBoard() const { return _loopBoard; }
    void setLoopBoard(bool nv) { _loopBoard = nv; }

private:
    int _newBoardWidth=8;
    int _newBoardHeight=8;
    bool _loopBoard=true;

};

#endif // NEWBOARDOPTIONS_H
