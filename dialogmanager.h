#ifndef DIALOGMANAGER_H
#define DIALOGMANAGER_H

#include <QObject>

class BoardModel;

class DialogManager : public QObject
{
    Q_OBJECT
public:

    explicit DialogManager(QWidget *parent);
    ~DialogManager();

    const QString getBoardFileName() const { return currentBoardFileName; }
    const QString getCurrentSessionFileName() const { return currentSessionFileName; }

public Q_SLOTS:
    bool showOpenBoard();
    bool showOpenSession();
    bool showSaveBoard();
    bool showSaveSession();

private:
    const QString getFileDialogFileSelection() const;
    bool setCurrentBoardFileName(const QString);
    bool setCurrentSessionFileName(const QString);
    QString currentBoardFileName;
    QString currentSessionFileName;
    QWidget *parentWidget;
};

#endif // DIALOGMANAGER_H
