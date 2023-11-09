#include "myview.h"

MyView::MyView(QWidget *parent) : QWidget(parent)
{
    currentChar = 'P';
    currentLayer = 0;
    fieldSize = 35;
    firstColumnToShow = 0;
    firstRankToShow = 0;
    ranksToShow = 0;
    columnsToShow = 0;
    boardWasMoved = false;
    boardWasClickedPoint = QPoint();
    setCursor(QCursor(QPixmap(":/icons/media-stop.png")));

    setMouseTracking(true);
}

MyView::~MyView()
{
    for (int i = 0; i<myBoards.size(); i++)
    {
        delete myBoards[i];
    }
}

int MyView::getCurrentLayer() const
{
    return currentLayer;
}

void MyView::setCurrentLayer(int value)
{
    currentLayer = value;
    emit layerChangedSignal(currentLayer + 1);
}

char MyView::getCurrentChar() const
{
    return currentChar;
}

void MyView::setCurrentChar(char value)
{
    currentChar = value;
}

QVector<MyBoard *> MyView::getMyBoards() const
{
    return myBoards;
}

void MyView::setMyBoards(const QVector<MyBoard *> &value)
{
    myBoards = value;
}

int MyView::getFieldSize() const
{
    return fieldSize;
}

void MyView::setFieldSize(int value)
{
    fieldSize = value;
}

void MyView::deleteBoards()
{
    myBoards.clear();
    myBoards.squeeze();
}

MyBoard* MyView::AddBoard(int rank, int column)
{
    MyBoard* newBoard = new MyBoard(rank, column);
    myBoards.append(newBoard);

    currentLayer = myBoards.size() - 1;
    emit layerChangedSignal(currentLayer + 1);

    qDebug()<<"rank = "<<rank;
    qDebug()<<"col = "<<column;

    return newBoard;
}

void MyView::SetScale(int ranks, int columns)
{
    ranksToShow = ranks;
    columnsToShow = columns;
    emit ranksColumnsToShowChangedSignal(ranksToShow, columnsToShow);
    firstColumnToShow = 0;
    firstRankToShow = 0;
    emit setFirstRankColumnToShowSignal(0,0);
    setFieldSize(std::min(height()/ranks, width()/columns));

    repaint();

}

int MyView::getColumnsToShow() const
{
    return columnsToShow;
}

int MyView::getRanksToShow() const
{
    return ranksToShow;
}

void MyView::setRanksColumnsToShow(int ranks, int columns)
{
    ranksToShow = ranks;
    columnsToShow = columns;
    repaint();
}

int MyView::getFirstColumnToShow() const
{
    return firstColumnToShow;
}

void MyView::setFirstColumnToShow(int value)
{
    firstColumnToShow = value;
}

int MyView::getFirstRankToShow() const
{
    return firstRankToShow;
}

void MyView::setFirstRankToShow(int value)
{
    firstRankToShow = value;
}

void MyView::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        int rank = 0;
        while (event->pos().y() - rank*fieldSize > fieldSize)
        {
            rank++;
        }

        int column = 0;
        while (event->pos().x() - column*fieldSize > fieldSize)
        {
            column++;
        }

        myBoards.at(currentLayer)->setChar(currentChar, (rank + firstRankToShow)*myBoards.at(0)->getColumns() + column + firstColumnToShow);
        repaint();
    }
    else if (event->button() == Qt::RightButton)
    {
        boardWasMoved = false;
        boardWasClickedPoint = event->pos();
    }
}

void MyView::paintEvent(QPaintEvent *event)
{
    if (!myBoards.size()) { return; }

    QPainter painter (this);

    painter.setFont(QFont("Times", fieldSize/5, 50));

    int ranks = myBoards.at(currentLayer)->getRanks();
    int columns = myBoards.at(currentLayer)->getColumns();

    for (int r = 0; r < ranks - firstRankToShow && r <= ranksToShow; r++)
    {
        for (int c = 0; c < columns - firstColumnToShow && c <= columnsToShow; c++)
        {
            int index = (r+firstRankToShow) *columns + c+firstColumnToShow;
            QColor colorToDraw = (c+r)%2 == 0 ? Qt::white : QColor(240,240,255,255);


            if (myBoards.at(currentLayer)->getBoardData().at(index)== 'P')
            {
                colorToDraw = Qt::black;
            }
            QRect rectToDraw = QRect(c*fieldSize, r*fieldSize, fieldSize, fieldSize);

            painter.fillRect(rectToDraw, colorToDraw);

            if(r && r != ranksToShow - 1
                    && r != ranks - 1
                    && r < ranksToShow - 1
                    && (!c || c == qMin(columnsToShow, columns) - 1))
            {
                QString str;
                str.setNum(r+firstRankToShow+1);
                if (myBoards.at(currentLayer)->getBoardData().at(index)== 'P')
                {
                    painter.setPen(QPen(QBrush(Qt::lightGray), 5));
                }
                else
                {
                    painter.setPen(QPen(QBrush(Qt::darkGray), 5));
                }
                painter.drawText(rectToDraw, Qt::AlignCenter, str);
            }

            if(c && c != columnsToShow - 1
                    && c != columns - 1
                    && c < columnsToShow - 1
                    && (!r || r == qMin(ranksToShow, ranks) - 1))
            {
                QString str;
                str.setNum(c+firstColumnToShow+1);
                if (myBoards.at(currentLayer)->getBoardData().at(index)== 'P')
                {
                    painter.setPen(QPen(QBrush(Qt::lightGray), 5));
                }
                else
                {
                    painter.setPen(QPen(QBrush(Qt::darkGray), 5));
                }
                painter.drawText(rectToDraw, Qt::AlignCenter, str);
            }
        }
    }

    int w = qMin(width(), fieldSize*(columns-firstColumnToShow)) - 1;
    int h = qMin(height(), fieldSize*(ranks-firstRankToShow)) - 1;
    QRect rectToDraw (0, 0, w, h);
    painter.setPen(Qt::darkGray);
    painter.drawRect(rectToDraw);
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
    int rank = 0;
    while (event->pos().y() - rank*fieldSize > fieldSize)
    {
        rank++;
    }

    int column = 0;
    while (event->pos().x() - column*fieldSize > fieldSize)
    {
        column++;
    }

    QString rankStr;
    rankStr.setNum(rank + firstRankToShow + 1);
    QString columnStr;
    columnStr.setNum(column + firstColumnToShow + 1);
    QToolTip::showText(event->globalPos(), QString("Rank = " + rankStr + "\nColumn = " + columnStr), this, geometry(), 1000);

    if (event->buttons()==Qt::LeftButton)
    {
        if(myBoards.at(currentLayer)->getColumns()*fieldSize > event->pos().x()
                && myBoards.at(currentLayer)->getRanks()*fieldSize > event->pos().y()
                && event->pos().x() > 0
                && event->pos().y() > 0
                && width() > event->pos().x()
                && height() > event->pos().y())
        {
            if (currentChar == 'P') { setCursor(QCursor(QPixmap(":/icons/media-stop.png"))); }
            else { setCursor(QCursor(QPixmap(":/icons/media-stop-outline.png"))); }

            myBoards.at(currentLayer)->setChar(currentChar, (rank + firstRankToShow)*myBoards.at(0)->getColumns() + column + firstColumnToShow);

            repaint();
        }
        else
        {
            unsetCursor();
            return;
        }

    }

    else if (event->buttons()==Qt::RightButton)
    {
        if(myBoards.at(currentLayer)->getColumns()*fieldSize > event->pos().x()
                && myBoards.at(currentLayer)->getRanks()*fieldSize > event->pos().y()
                && event->pos().x() > 0
                && event->pos().y() > 0
                && width() > event->pos().x()
                && height() > event->pos().y())
        {
            setCursor(Qt::PointingHandCursor);

            boardWasMoved = true;

            if (myBoards.at(currentLayer)->getColumns()*fieldSize <= width()
                    && myBoards.at(currentLayer)->getRanks()*fieldSize <= height())
            {
                return;
            }

            int deltaX = (event->pos().x() - boardWasClickedPoint.x())/fieldSize;
            int deltaY = (event->pos().y() - boardWasClickedPoint.y())/fieldSize;

            if (!deltaX && !deltaY) { return; }

            if (deltaX)
            {
                deltaX/=std::abs(deltaX);

                if (deltaX > 0 && firstColumnToShow == 0) { return; }
                if (deltaX < 0 && firstColumnToShow >= myBoards.at(currentLayer)->getColumns() - getColumnsToShow()) { return; }

                boardWasClickedPoint.setX(boardWasClickedPoint.x() + fieldSize*deltaX);
                firstColumnToShow -= deltaX;
            }

            if (deltaY)
            {
                deltaY/=std::abs(deltaY);

                if (deltaY > 0 && firstRankToShow == 0) { return; }
                if (deltaY < 0 && firstRankToShow >= myBoards.at(currentLayer)->getRanks() - getRanksToShow()) { return; }

                boardWasClickedPoint.setY(boardWasClickedPoint.y() + fieldSize*deltaY);
                firstRankToShow -= deltaY;
            }

            emit setFirstRankColumnToShowSignal(firstRankToShow, firstColumnToShow);

            repaint();
        }

        else
        {
            unsetCursor();
            return;
        }
    }

}

void MyView::wheelEvent(QWheelEvent *event)
{
    if (this->rect().contains(event->pos()))
    {
        int w = event->delta() > 0 ? 1 : -1;

        if (fieldSize <= 1 && w < 0)   {   return; }

        if (myBoards.at(currentLayer)->getColumns()*fieldSize <= width()
                && myBoards.at(currentLayer)->getRanks()*fieldSize <= height()
                && w < 0)
        { return; }


        fieldSize += w;

        ranksToShow = qMin(height()/fieldSize, myBoards.at(currentLayer)->getRanks());
        columnsToShow = qMin(width()/fieldSize, myBoards.at(currentLayer)->getColumns());

        emit ranksColumnsToShowChangedSignal(ranksToShow, columnsToShow);
        repaint();
    }
}


void MyView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
        {
            if (boardWasMoved == false)
            {

                qDebug()<<"right button working";

                int width = getMyBoards().at(getCurrentLayer())->getColumns();
                int height = getMyBoards().at(getCurrentLayer())->getRanks();

                QImage currentImage(width, height, QImage::Format_ARGB32);
                QRgb black = qRgb(0,0,0);
                QRgb white = qRgb(255,255,255);

                for (int h = 0; h < height; h++)
                {
                    for (int w = 0; w < width; w++)
                    {
                        if (getMyBoards().at(getCurrentLayer())->getBoardData().at(width * h + w) == 'P')
                        {
                            currentImage.setPixel(w, h, black);
                        }
                        else
                        {
                            currentImage.setPixel(w, h, white);
                        }
                    }
                }

                QPoint currentPos(event->pos().x()/getFieldSize(), event->pos().y()/getFieldSize());

                if (MyAlgorithm::posIsInsideObject(currentImage, currentPos) == true)
                {
                    QMessageBox::information(this, "Grab an Object", "You clicked inside an object", QMessageBox::Ok);
                }
                else
                {
                    QMessageBox::information(this, "Grab an Object", "You clicked outside objects", QMessageBox::Ok);
                }
            }
            else
            {
                boardWasMoved = false;

                if (currentChar == 'P') { setCursor(QCursor(QPixmap(":/icons/media-stop.png"))); }
                else { setCursor(QCursor(QPixmap(":/icons/media-stop-outline.png"))); }
            }
    }
}

void MyView::resizeEvent(QResizeEvent *event)
{
    int ranks = std::min(height()/fieldSize, myBoards.at(currentLayer)->getRanks());
    int columns = std::min(width()/fieldSize, myBoards.at(currentLayer)->getColumns());

    if (ranks == myBoards.at(currentLayer)->getRanks() || columns == myBoards.at(currentLayer)->getColumns())
//        fieldSize == qMin(height()/myBoards.at(currentLayer)->getRanks(), width()/myBoards.at(currentLayer)->getColumns());
    {  /*SetScale(ranks,columns);*/ }
///////////////////////////////////////////////// fix
    setRanksColumnsToShow(ranks, columns);
    emit ranksColumnsToShowChangedSignal(ranks, columns);
}

