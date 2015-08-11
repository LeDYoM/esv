#include "filemanager.h"
#include "boardmodel.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

FileManager::~FileManager()
{

}

BoardData FileManager::loadBoard(const QString fName)
{
    QFile file(fName);

    bool result = file.open(QIODevice::ReadOnly);
    if (result)
    {
        QDataStream in(&file);
        QString format;

        in >> format;
        qDebug() << "Read file format: " << format;
        QSize temp;
        in >> temp;
        BoardData bData(temp);
        //in >> bData.closed;
        in >> bData.data;

        file.close();
        return bData;
    }
    return BoardData(QSize(0,0));
}

bool FileManager::saveBoard(const QString fName, BoardFormatType bft, const BoardModel * const bModel)
{
    QFile file(fName);

    bool result = file.open(QIODevice::WriteOnly);
    if (result)
    {
        const BoardData &bData = bModel->getBoardData();
        QDataStream out(&file);

        switch (bft)
        {
        default:
        case BoardFormatType::BinaryNative:
            out << QString("esv bf0.1");
            out << bData.size;
            //out << bData.closed;
            out << bData.data;
            break;
        case BoardFormatType::TextNative:
            break;
        }
        file.flush();
        file.close();
        return true;
    }
    return false;
}
