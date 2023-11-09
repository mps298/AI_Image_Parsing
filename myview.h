#ifndef MYVIEW_H
#define MYVIEW_H

#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QToolTip>
#include <QMessageBox>
#include "myboard.h"
#include "myalgorithm.h"

class MyView : public QWidget
{
    Q_OBJECT
public:
    explicit MyView(QWidget *parent = nullptr);
    ~MyView();

    int getCurrentLayer() const;
    void setCurrentLayer(int value);

    char getCurrentChar() const;
    void setCurrentChar(char value);

    QVector<MyBoard*> getMyBoards() const;
    void setMyBoards(const QVector<MyBoard *> &value);

    int getFieldSize() const;
    void setFieldSize(int value);

    void deleteBoards();

    int getFirstRankToShow() const;
    void setFirstRankToShow(int value);

    int getFirstColumnToShow() const;
    void setFirstColumnToShow(int value);

    int getRanksToShow() const;
    void setRanksColumnsToShow(int ranks, int columns);

    int getColumnsToShow() const;


signals:
    void layerChangedSignal(int);
    void ranksColumnsToShowChangedSignal(int, int);
    void setFirstRankColumnToShowSignal(int, int);

public slots:

    MyBoard* AddBoard(int rank, int column);
    void SetScale (int ranks, int columns);

private:
    char currentChar;
    int currentLayer;
    int fieldSize;
    QVector<MyBoard*> myBoards;

    int firstRankToShow;
    int firstColumnToShow;

    int ranksToShow;
    int columnsToShow;


    bool boardWasMoved;
    QPoint boardWasClickedPoint;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // MYVIEW_H
