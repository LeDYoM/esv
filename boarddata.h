#ifndef BOARDDATA_H
#define BOARDDATA_H

#include <QSize>
#include <QVector>

template <typename T>
struct Matrix
{
    QSize size;
    using MatrixColumn = QVector<T>;
    QVector<MatrixColumn> data;

    explicit Matrix(QSize size_)
    {
        size = size_;
        createData();
    }

    Matrix(const Matrix<T> &other)
    {
        size = other.size;
        data = other.data;
    }

    MatrixColumn &operator[](int index) { return data[index]; }
    void createData()
    {
        data.clear();
        for (auto x = 0; x < size.width(); ++x)
        {
            MatrixColumn column;
            for (auto y=0;y<size.height();++y)
            {
                column.push_back(T(0));
            }
            data.push_back(column);
        }
    }

};

class BoardData : public Matrix<qint32>
{
public:
    using Matrix<qint32>::Matrix;

    bool loopBoard() const { return _loopBoard; }
    void setLoopBoard(bool nv) { _loopBoard = nv; }
private:
    bool _loopBoard=true;
};

#endif // BOARDDATA_H
