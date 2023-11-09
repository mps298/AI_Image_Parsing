#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include <QInputDialog>
#include <QScrollArea>
#include <QRect>
#include <QScreen>
#include <QCursor>

#include "myview.h"
#include "myalgorithm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPoint getClickPos() const;
    void setClickPos(const QPoint &value);

private slots:
    void setFirstRankColumnToShowSlot(int rank, int column);

    void on_removePixelButton_clicked();
    void on_addPixelButton_clicked();

    void on_actionSave_Pixels_triggered();
    void on_actionDownload_Pixels_triggered();
    void on_actionReset_Pixels_triggered();
    void on_actionSet_Board_Size_triggered();
    void on_actionCalculate_Probability_triggered();
    void on_actionChoose_Layer_triggered();
    void on_actionAdd_Layer_triggered();
    void on_actionDelete_Layer_triggered();

    void on_verticalSlider_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);

    void on_left20Button_clicked();
    void on_leftButton_clicked();
    void on_up20Button_clicked();
    void on_upButton_clicked();
    void on_right20Button_clicked();
    void on_rightButton_clicked();
    void on_down20Button_clicked();
    void on_downButton_clicked();

    void on_topleft_Button_clicked();
    void on_bottomleft_Button_clicked();
    void on_topright_Button_clicked();
    void on_bottomright_Button_clicked();

    void ranksColumnsToShowChangedSlot(int ranks, int columns);
    void on_actionParse_Image_triggered();



    void on_fullSizeButton_clicked();

private:
    Ui::MainWindow *ui;
    
    MyView* m_view;

    int countFilesSaved;
    QString currentFileOpened;
    bool sizeWasChanged;
    int ranksToShow;
    int columnsToShow;

    QFlags<Qt::WindowState> oldWindowState;


    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // MAINWINDOW_H
