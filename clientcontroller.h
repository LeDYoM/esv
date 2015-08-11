#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QSize>
#include <QPoint>

class BoardModel;
class Utils;

class ClientController : public QObject
{
	Q_OBJECT

    Q_PROPERTY(QSize boardSize READ boardSize WRITE setBoardSize)
    Q_PROPERTY(double densiness READ densiness WRITE setDensiness)
    Q_PROPERTY(int lowp READ lowp WRITE setLowp)
    Q_PROPERTY(int highp READ highp WRITE setHighp)
    Q_PROPERTY(int createp READ createp WRITE setCreatep)
    Q_PROPERTY(quint16 nStates READ nStates WRITE setNStates)
public:
    ClientController(QObject *parent);
	~ClientController();

    void loadQMLClient(const QString fileName);
    int randomInt(const int max) const;

    void getNewStartBoard(BoardModel *const toFill);
    void getNewStep(BoardModel *const toFill);
    const QSize &boardSize() const { return _boardSize; }
    void setBoardSize(const QSize &ns) { _boardSize = ns; }

    double densiness() const { return _densiness; }
    void setDensiness(double nv) { _densiness = nv; }

    int lowp() const { return _lowp; }
    void setLowp(int nv) { _lowp = nv; }

    int highp() const { return _highp; }
    void setHighp(int nv) { _highp = nv; }

    int createp() const { return _createp; }
    void setCreatep(int nv) { _createp = nv; }

    quint16 nStates() const { return _nstates; }
    void setNStates(quint16 nv) { _nstates=nv; }

private:
    QSize _boardSize = QSize(8,8);
    double _densiness = 0.2;
    int _lowp = 1;
    int _highp = 4;
    int _createp = 3;
    quint16 _nstates=2;

};

#endif // CLIENTCONTROLLER_H
