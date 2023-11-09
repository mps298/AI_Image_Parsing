#ifndef MYBOARD_H
#define MYBOARD_H

#include <QVector>
#include <QDebug>

class MyBoard
{
public:
    MyBoard(int r, int c);

    int getRanks() const;
    void setRanks(int value);

    int getColumns() const;
    void setColumns(int value);

    QVector<char> getBoardData() const;
    void setBoardData(const QVector<char> &value);

    void addCharToBoard(char ch);
    void setChar (char ch, int index);
    void resetBoard();

private:
    int ranks;
    int columns;
    QVector<char> boardData;
};

#endif // MYBOARD_H
