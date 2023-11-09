#include "myboard.h"

MyBoard::MyBoard(int r, int c): ranks(r), columns(c)
{
    boardData.resize(ranks*columns);
    boardData.fill(' ');
}

int MyBoard::getRanks() const
{
    return ranks;
}

void MyBoard::setRanks(int value)
{
    ranks = value;
}

int MyBoard::getColumns() const
{
    return columns;
}

void MyBoard::setColumns(int value)
{
    columns = value;
}

QVector<char> MyBoard::getBoardData() const
{
    return boardData;
}

void MyBoard::setBoardData(const QVector<char> &value)
{
    boardData = value;
}

void MyBoard::addCharToBoard(char ch)
{
    boardData.append(ch);
}

void MyBoard::setChar(char ch, int index)
{
    if (index<0 || index>=boardData.size())
    {
        qDebug()<<index<<" boarddatasize "<<boardData.size()<<" is out of range!";
        return;
    }

    boardData[index] = ch;
}

void MyBoard::resetBoard()
{
    boardData.fill(' ');
}

