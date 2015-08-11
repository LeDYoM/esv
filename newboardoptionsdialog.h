#ifndef NEWBOARDOPTIONSDIALOG_H
#define NEWBOARDOPTIONSDIALOG_H

#include <QDialog>

class QSlider;
class QSpinBox;
class QCheckBox;
class NewBoardOptions;

class NewBoardOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewBoardOptionsDialog( const NewBoardOptions *const nbo,QWidget *parent = 0);

    void updateNewBoardOptions(NewBoardOptions *const nbo);
private:
    QSlider *sliderWidth;
    QSlider *sliderHeight;
    QSpinBox *boardWidthSpinBox;
    QSpinBox *boardHeightSpinBox;
    QCheckBox *loopCheck;
};

#endif // NEWBOARDOPTIONSDIALOG_H
