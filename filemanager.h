#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include "boardmodel.h"

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(QObject *parent=nullptr);
    ~FileManager();

    enum class BoardFormatType
    {
        BinaryNative,
        TextNative
    };

    enum class SessionFormatType
    {
        BinaryNative,
        TextNative
    };

    BoardData loadBoard(const QString fName);
    bool saveBoard(const QString fName, BoardFormatType bft, const BoardModel *const bModel);

};

#endif // FILEMANAGER_H
