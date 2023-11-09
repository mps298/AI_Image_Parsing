#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include <QObject>
#include <QWindow>
#include <QDebug>
#include <QVector>
#include <QImage>
#include <QRgb>
#include <QLabel>
#include <QPixmap>
#include <QSet>
#include <QList>

class MyAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit MyAlgorithm(QObject *parent = nullptr);

    static double computeProbability(const QList<QString>& myStrings, const QString& stringToCompare);
    static QImage coloredToBlackWhite(const QImage& image, int difference = 20);
    static QImage noiseReduction(const QImage &image, int iteration = 6);
    static QImage noiseReduction_median(const QImage &image, int gridSize = 11);
    static bool posIsInsideObject(const QImage &image, const QPoint &pos);

signals:

public slots:
};

#endif // MYALGORITHM_H
