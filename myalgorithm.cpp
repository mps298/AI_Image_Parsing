#include "myalgorithm.h"

MyAlgorithm::MyAlgorithm(QObject *parent) : QObject(parent)
{

}


double MyAlgorithm::computeProbability(const QList<QString>& myStrings, const QString& stringToCompare)
{
    if (myStrings.isEmpty())
    {
        qDebug()<<"Nothing to compare!";
        return -2;
    }

    int length = stringToCompare.size();
    auto it = myStrings.begin();

    while (it!=myStrings.end())
    {
        if ((*it).size()!=length)
        {
            qDebug()<<"Different length of strings!";
            return -1;
        }
        ++it;
    }

    //we use doubles to save accuracy when calculate

    double coeff = 0.0; //coeficient for trained dataset

    QVector<double> myWeights;  //vector of weights for trained dataset
    myWeights.resize(length);
    myWeights.fill(0.0);

    double var = 0.0; //temporary variable for counting a coeficient
    double numberOfSamples = static_cast<double>(myStrings.size());

    double pix = 0.0;    //number of pixels to be taken for trained dataset

    double probability = 0.0;    //probability of string4, result to return

    for(int x = 0; x < length; x++)
    {
        it = myStrings.begin();

        while (it!=myStrings.end())
        {
            if ((*it).at(x) == QChar('P'))
            {
                pix++;
                break;
            }
            ++it;
        }

    }

    for(int x = 0; x < length; x++)
    {
        it = myStrings.begin();

        while (it!=myStrings.end())
        {
            if ((*it).at(x) == QChar('P'))
            {
                myWeights[x] = myWeights[x]+1;
            }
            ++it;
        }

        myWeights[x] = myWeights[x]/numberOfSamples;
        var = var+myWeights[x];
    }

    if (pix == 0 || var == 0)
    {
        return 0;
    }

    coeff = pix/var;

    for(int x = 0; x < length; x++)
    {
        probability = probability+(myWeights[x]*(stringToCompare.at(x) == QChar('P'))*coeff)/pix;
    }

    return probability;
}


QImage MyAlgorithm::coloredToBlackWhite(const QImage &image, int difference)
{
    QImage image32 = image.convertToFormat(QImage::Format_ARGB32);
    qDebug()<<image32;

    int width = image32.width();
    int height = image32.height();

    QRgb white = qRgb(255, 255, 255);
    QRgb black = qRgb(0, 0, 0);
    QRgb value;                      //rgb value of pixel of banana
    QRgb value_left;                 //rgb value of neighbor
    QRgb value_right;                //rgb value of neighbor
    QRgb value_top;                   //rgb value of neighbor
    QRgb value_below;                 //rgb value of neighbor
    QRgb value_leto;                   //rgb value of neighbor left top
    QRgb value_rito;                  //rgb value of neighbor  right top
    QRgb value_lebe;                  //rgb value of neighbor  left below
    QRgb value_ribe;                    //rgb value of neighbor right below

    int r_image;
    int g_image;
    int b_image;
    int left_r;
    int left_g;
    int left_b;
    int right_r;
    int right_g;
    int right_b;
    int top_r;
    int top_g;
    int top_b;
    int below_r;
    int below_g;
    int below_b;
    int leto_r;
    int leto_g;
    int leto_b;
    int rito_r;
    int rito_g;
    int rito_b;
    int lebe_r;
    int lebe_g;
    int lebe_b;
    int ribe_r;
    int ribe_g;
    int ribe_b;

    QImage blackWhiteImage (width, height, QImage::Format_ARGB32);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            value = image32.pixel(w, h);

            if(w == 0 || w == width-1 || h == 0 || h == height-1)
            {
                blackWhiteImage.setPixel(w, h, white); //white border around bw, special case
            }
            else
            {
                value_left = image32.pixel(w-1,h);
                value_right = image32.pixel(w+1,h);
                value_top = image32.pixel(w,h+1);
                value_below = image32.pixel(w,h-1);
                value_leto = image32.pixel(w-1,h+1);
                value_rito = image32.pixel(w+1,h+1);
                value_lebe = image32.pixel(w-1,h-1);
                value_ribe = image32.pixel(w+1,h-1);
                left_r = qRed(value_left);
                left_g = qGreen(value_left);
                left_b = qBlue(value_left);
                right_r = qRed(value_right);
                right_g = qGreen(value_right);
                right_b = qBlue(value_right);
                top_r = qRed(value_top);
                top_g = qGreen(value_top);
                top_b = qBlue(value_top);
                below_r = qRed(value_below);
                below_g = qGreen(value_below);
                below_b = qBlue(value_below);
                leto_r = qRed(value_leto);
                leto_g = qGreen(value_leto);
                leto_b = qBlue(value_leto);
                rito_r = qRed(value_rito);
                rito_g = qGreen(value_rito);
                rito_b = qBlue(value_rito);
                lebe_r = qRed(value_lebe);
                lebe_g = qGreen(value_lebe);
                lebe_b = qBlue(value_lebe);
                ribe_r = qRed(value_ribe);
                ribe_g = qGreen(value_ribe);
                ribe_b = qBlue(value_ribe);
                r_image = qRed(value);
                g_image = qGreen(value);
                b_image = qBlue(value);

                if  (
                     (
                         (   (abs(r_image-left_r)>difference)    ||
                             (abs(g_image-left_g)>difference)    ||
                             (abs(b_image-left_b)>difference)
                             )

                         ||

                         (   (abs(r_image-right_r)>difference)   ||
                             (abs(g_image-right_g)>difference)   ||
                             (abs(b_image-right_b)>difference)
                             )

                         ||

                         (   (abs(r_image-top_r)>difference)     ||
                             (abs(g_image-top_g)>difference)     ||
                             (abs(b_image-top_b)>difference)
                             )

                         ||

                         (   (abs(r_image-below_r)>difference)   ||
                             (abs(g_image-below_g)>difference)   ||
                             (abs(b_image-below_b)>difference)
                             )
                         )

                     ||

                     (
                         (   (abs(r_image-leto_r)>difference)    ||
                             (abs(g_image-leto_g)>difference)    ||
                             (abs(b_image-leto_b)>difference)
                             )

                         ||

                         (   (abs(r_image-rito_r)>difference)    ||
                             (abs(g_image-rito_g)>difference)    ||
                             (abs(b_image-rito_b)>difference)
                             )

                         ||

                         (   (abs(r_image-lebe_r)>difference)    ||
                             (abs(g_image-lebe_g)>difference)    ||
                             (abs(b_image-lebe_b)>difference)
                             )

                         ||

                         (   (abs(r_image-ribe_r)>difference)    ||
                             (abs(g_image-ribe_g)>difference)    ||
                             (abs(b_image-ribe_b)>difference)
                             )
                         )
                     )
                {
                    blackWhiteImage.setPixel(w, h, black);
                }
                else
                {
                    blackWhiteImage.setPixel(w, h, white);
                }
            }
        }
    }

    return blackWhiteImage;
}

QImage MyAlgorithm::noiseReduction(const QImage& image, int iteration)
{
    QImage resultImage = image.convertToFormat(QImage::Format_ARGB32);

    int width = resultImage.width();
    int height = resultImage.height();

    QRgb white = qRgb(255, 255, 255);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (resultImage.pixel(w,h) == white)  {   continue; }

            int directionsChecked = 0;
            int count = 0;

            //up
            for (int i = 0; i < iteration; i++)
            {
                if (h - i < 0)  {   break;  } //edge reached
                if (resultImage.pixel(w, h-i) == white)   {   break;    }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //up-right
            for (int i = 0; i < iteration; i++)
            {
                if (h - i < 0 || w + i >= width) {   break;  } // edge reached
                if (resultImage.pixel(w+i, h-i) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //right
            for (int i = 0; i < iteration; i++)
            {
                if (w + i >= width) {   break;  } // edge reached
                if (resultImage.pixel(w+i, h) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //down-right
            for (int i = 0; i < iteration; i++)
            {
                if (h + i >= height || w + i >= width) {   break;  } // edge reached
                if (resultImage.pixel(w+i, h+i) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //down
            for (int i = 0; i < iteration; i++)
            {
                if (h + i >= height) {   break;  } // edge reached
                if (resultImage.pixel(w, h+i) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //down-left
            for (int i = 0; i < iteration; i++)
            {
                if (h + i >= height || w - i < 0) {   break;  } // edge reached
                if (resultImage.pixel(w-i, h+i) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //left
            for (int i = 0; i < iteration; i++)
            {
                if (w - i < 0) {   break;  } // edge reached
                if (resultImage.pixel(w-i, h) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }
            count = 0;

            //up-left
            for (int i = 0; i < iteration; i++)
            {
                if (h - i < 0 || w - i < 0) {   break;  } // edge reached
                if (resultImage.pixel(w-i, h-i) == white) {   break;  }
                count++;
            }
            if (count == iteration) {   directionsChecked++; }

            if (!directionsChecked)
            {
                resultImage.setPixel(w,h,white);
            }
        }
    }

return resultImage;

}

QImage MyAlgorithm::noiseReduction_median(const QImage &image, int gridSize)
{
    if (!gridSize%2) { gridSize++; } //be sure gridSize is odd, to calculate median correctly

    QImage resultImage = image.convertToFormat(QImage::Format_ARGB32);

    int croppedWidth = resultImage.width() - resultImage.width()%gridSize;
    int croppedHeight = resultImage.height() - resultImage.height()%gridSize;

    int xRemain = resultImage.width() - croppedWidth;
    int yRemain = resultImage.height()% - croppedHeight;

    if (xRemain || yRemain)
    {
        resultImage = resultImage.copy(xRemain/2, yRemain/2, croppedWidth, croppedHeight);
    }

    QRgb white = qRgb(255, 255, 255);
    QRgb black = qRgb(0, 0, 0);

    for (int row = 0; row < resultImage.height(); row += gridSize)
    {
        for (int col = 0; col < resultImage.width(); col += gridSize)
        {
            qDebug()<<"c "<<col<<" r "<<row;

            QList<int> redValuesList;
            QList<int> greenValuesList;
            QList<int> blueValuesList;

            //counting medians for each grid
            for (int r = row; r < row + gridSize; r++)
            {
                for (int c = col; c < col + gridSize; c++)
                {
                    redValuesList.append(qRed(resultImage.pixel(c,r)));
                    greenValuesList.append(qGreen(resultImage.pixel(c,r)));
                    blueValuesList.append(qBlue(resultImage.pixel(c,r)));
                }
            }
             qDebug()<<"size r"<<redValuesList.size();

            std::sort(redValuesList.begin(), redValuesList.end());
            std::sort(greenValuesList.begin(), greenValuesList.end());
            std::sort(blueValuesList.begin(), blueValuesList.end());

            int redMedian = redValuesList.at((redValuesList.size()+1)/2);
            int greenMedian = greenValuesList.at((greenValuesList.size()+1)/2);
            int blueMedian = blueValuesList.at((blueValuesList.size()+1)/2);

            for (int r = row; r < row + gridSize; r++)
            {
                for (int c = col; c < col + gridSize; c++)
                {
                    if (abs(static_cast<double>(qRed(resultImage.pixel(c,r))) / redMedian) > 1.2
                        || abs(static_cast<double>(qGreen(resultImage.pixel(c,r))) / greenMedian) > 1.2
                        || abs(static_cast<double>(qBlue(resultImage.pixel(c,r))) / blueMedian) > 1.2)
                    {
                        resultImage.setPixel(c, r, black);
                    }
                    else
                    {
                        resultImage.setPixel(c, r, white);
                    }
                }
            }

        }
    }

    return resultImage;
}

bool MyAlgorithm::posIsInsideObject(const QImage &image, const QPoint &pos)
{
    QImage image32 = image.convertToFormat(QImage::Format_ARGB32);

    int width = image32.width();
    int height = image32.height();

    QRgb black = qRgb(0, 0, 0);

    //up
    int iter = 0;

    while   (true)
    {
        if (image32.pixel(pos.x(), pos.y()-iter) == black) {   break; }
        if (pos.y() - iter == 0)   {   return false;   }
        iter++;
    }

    //up-right
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x()+iter, pos.y()-iter) == black) {   break; }
        if (pos.y() - iter == 0 || pos.x() + iter == width)   {   return false;   }
        iter++;
    }

    //right
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x()+iter, pos.y()) == black) {   break; }
        if (pos.x() + iter == width)   {   return false;   }
        iter++;
    }

    //down-right
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x()+iter, pos.y()+iter) == black) {   break; }
        if (pos.y() + iter == height || pos.x() + iter == width)   {   return false;   }
        iter++;
    }

    //down
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x(), pos.y()+iter) == black) {   break; }
        if (pos.y() + iter == height)   {   return false;   }
        iter++;
    }

    //down-left
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x()-iter, pos.y()+iter) == black) {   break; }
        if (pos.y() + iter == height || pos.x() - iter == 0)   {   return false;   }
        iter++;
    }

    //left
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x()-iter, pos.y()) == black) {   break; }
        if (pos.x() - iter == 0)   {   return false;   }
        iter++;
    }

    //up-left
    iter = 0;
    while   (true)
    {
        if (image32.pixel(pos.x()-iter, pos.y()-iter) == black) {   break; }
        if (pos.y() - iter == 0 || pos.x() - iter == 0)   {   return false;   }
        iter++;
    }

    return true;
}
