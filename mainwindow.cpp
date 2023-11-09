#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_view = ui->MyViewWidget;

    if (!QFile::exists("countFilesSaved.txt"))
    {
        ui->statusBar->showMessage("No files saved", 5000);
        countFilesSaved = 0;
    }
    else
    {
        QFile file("countFilesSaved.txt");
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            ui->statusBar->showMessage("No files saved", 1500);
            countFilesSaved = 0;
        }

        else
        {
            QString str = file.readAll();
            countFilesSaved = str.toInt();
            ui->statusBar->showMessage(str + " file(s) saved", 5000);
            file.close();
        }
    }

    currentFileOpened = QString();

    ui->verticalSlider->setEnabled(false);
    ui->up20Button->setEnabled(false);
    ui->upButton->setEnabled(false);
    ui->down20Button->setEnabled(false);
    ui->downButton->setEnabled(false);

    ui->horizontalSlider->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->right20Button->setEnabled(false);
    ui->left20Button->setEnabled(false);
    ui->leftButton->setEnabled(false);

    ui->topleft_Button->setEnabled(false);
    ui->topright_Button->setEnabled(false);
    ui->bottomleft_Button->setEnabled(false);
    ui->bottomright_Button->setEnabled(false);

    connect(m_view, SIGNAL(layerChangedSignal(int)), ui->currentLayerLabel, SLOT(setNum(int)));
    emit m_view->layerChangedSignal(m_view->getCurrentLayer()+1);

    sizeWasChanged = false;

//    m_view->setFieldSize(qMin(m_view->height()/20, m_view->width()/20));
//    qDebug()<<"fieldsize "<<m_view->getFieldSize();

    m_view->setRanksColumnsToShow(m_view->height()/m_view->getFieldSize(), m_view->width()/m_view->getFieldSize());
    m_view->AddBoard(m_view->getRanksToShow(),m_view->getColumnsToShow());

    connect(m_view, SIGNAL(ranksColumnsToShowChangedSignal(int, int)), this, SLOT(ranksColumnsToShowChangedSlot(int, int)));
    emit m_view->ranksColumnsToShowChangedSignal(m_view->getRanksToShow(), m_view->getColumnsToShow());

    m_view->SetScale(m_view->getRanksToShow(), m_view->getColumnsToShow());

    connect(m_view, SIGNAL(setFirstRankColumnToShowSignal(int,int)), this, SLOT(setFirstRankColumnToShowSlot(int,int)));

    oldWindowState = windowState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFirstRankColumnToShowSlot(int rank, int column)
{
    m_view->setFirstRankToShow(rank);
    ui->verticalSlider->setValue(rank+1);
    m_view->setFirstColumnToShow(column);
    ui->horizontalSlider->setValue(column+1);


    if (column <= 0)
    {
        ui->left20Button->setEnabled(false);
        ui->leftButton->setEnabled(false);
    }
    else
    {
        ui->left20Button->setEnabled(true);
        ui->leftButton->setEnabled(true);
    }

    if (rank <= 0)
    {
        ui->up20Button->setEnabled(false);
        ui->upButton->setEnabled(false);
    }

    else
    {
        ui->up20Button->setEnabled(true);
        ui->upButton->setEnabled(true);
    }

    if (rank >= m_view->getMyBoards().at(0)->getRanks() - ranksToShow)
    {
        ui->down20Button->setEnabled(false);
        ui->downButton->setEnabled(false);
    }
    else
    {
        ui->down20Button->setEnabled(true);
        ui->downButton->setEnabled(true);
    }

    if (column >= m_view->getMyBoards().at(0)->getColumns() - columnsToShow)
    {
        ui->right20Button->setEnabled(false);
        ui->rightButton->setEnabled(false);
    }
    else
    {
        ui->right20Button->setEnabled(true);
        ui->rightButton->setEnabled(true);
    }

    if (rank <= 0 && column <= 0)
    {
        ui->topleft_Button->setEnabled(false);
    }
    else
    {
        ui->topleft_Button->setEnabled(true);
    }

    if (rank <= 0 && column >= m_view->getMyBoards().at(0)->getColumns() - columnsToShow)
    {
        ui->topright_Button->setEnabled(false);
    }
    else
    {
        ui->topright_Button->setEnabled(true);
    }

    if  (rank >= m_view->getMyBoards().at(0)->getRanks() - ranksToShow && column<=0)
    {
        ui->bottomleft_Button->setEnabled(false);
    }
    else
    {
        ui->bottomleft_Button->setEnabled(true);
    }

    if (rank>=m_view->getMyBoards().at(0)->getRanks() - ranksToShow
            && column >= m_view->getMyBoards().at(0)->getColumns() - columnsToShow)
    {
        ui->bottomright_Button->setEnabled(false);
    }
    else
    {
        ui->bottomright_Button->setEnabled(true);
    }

    m_view->repaint();
}

void MainWindow::on_removePixelButton_clicked()
{
    m_view->setCurrentChar(' ');
    m_view->setCursor(QCursor(QPixmap(":/icons/media-stop-outline.png")));
}

void MainWindow::on_addPixelButton_clicked()
{
    m_view->setCurrentChar('P');
    m_view->setCursor(QCursor(QPixmap(":/icons/media-stop.png")));
}

void MainWindow::on_actionSave_Pixels_triggered()
{
    qDebug()<<"save pixels action works";

    QMessageBox messageBox;

    messageBox.setWindowTitle("Save pixels");
    messageBox.setWindowIcon(QIcon(":/icons/upload.png"));
    messageBox.setIconPixmap(QPixmap(":/icons/upload.png"));
    QPushButton* newFileButton = messageBox.addButton("New file", QMessageBox::YesRole);
    QPushButton* currentFileButton = messageBox.addButton("Current file", QMessageBox::NoRole);
    QPushButton* cancelButton = messageBox.addButton("Cancel", QMessageBox::NoRole);

    if(currentFileOpened.isEmpty())
    {
        currentFileButton->setDisabled(true);
        messageBox.setText("No file is opened\nYou can save the pixels to a new file");
    }

    else
    {
        if (sizeWasChanged)
        {
            currentFileButton->setDisabled(true);
            messageBox.setText("Size was changed\n\nYou can save it to a new file");
        }
        else
        {
            messageBox.setText("Where do you want to save it?\n\n"+currentFileOpened+" is open now");
        }

    }

    if (sizeWasChanged)
    {
        currentFileButton->setDisabled(true);
    }

    messageBox.exec();

    if (messageBox.clickedButton() == newFileButton)
    {

        QString strLayers;
        strLayers.setNum(m_view->getMyBoards().size());

        QString strRanks;
        strRanks.setNum(m_view->getMyBoards().at(0)->getRanks());

        QString strColumns;
        strColumns.setNum(m_view->getMyBoards().at(0)->getColumns());

        countFilesSaved++;
        QString tmp;
        QString newFileName("myboard_"+tmp.setNum(countFilesSaved)+"_size_"+
                            strLayers+"_"+strRanks+"_"+strColumns+".txt");
        qDebug()<<"newFileName "<<newFileName;

        QString str ="";



        str = str + strLayers + "\n";
        str = str + strRanks + "\n";
        str = str + strColumns + "\n";

        for (int i = 0; i<m_view->getMyBoards().size(); i++)
        {
            MyBoard* boardToSave = m_view->getMyBoards().at(i);

            for (int j = 0; j<boardToSave->getBoardData().size(); j++)
            {
                str+=boardToSave->getBoardData().at(j);
            }
        }
        qDebug()<<"str to save = "<<str;

        QFile file(newFileName);
        QTextStream stream(&file);

        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
             ui->statusBar->showMessage("Saving failed", 1500);
             return;
        }

        stream << str;
        stream.flush();
        file.close();

        ui->statusBar->showMessage("Board saved to file " + newFileName, 1500);
        currentFileOpened = newFileName;

        QFile file1("countFilesSaved.txt");
        QTextStream stream1(&file1);

        if (!file1.open(QIODevice::WriteOnly|QIODevice::Text))
        {
             ui->statusBar->showMessage("Saving number of files failed", 5000);
             return;
        }

        str = QString();
        str.setNum(countFilesSaved);
        qDebug()<<"countFilesSaved "<<str;
        stream1 << str;
        stream1.flush();
        file1.close();
    }

    else if (messageBox.clickedButton() ==  currentFileButton)
    {
        QString str ="";

        QString strLayers;
        strLayers.setNum(m_view->getMyBoards().size());

        QString strRanks;
        strRanks.setNum(m_view->getMyBoards().at(0)->getRanks());

        QString strColumns;
        strColumns.setNum(m_view->getMyBoards().at(0)->getColumns());

        str = str + strLayers + '\n';
        str = str + strRanks + '\n';
        str = str + strColumns + '\n';


        for (int i = 0; i<m_view->getMyBoards().size(); i++)
        {
             MyBoard* boardToSave = m_view->getMyBoards().at(i);

            for (int j = 0; j<boardToSave->getBoardData().size(); j++)
            {
                str+=boardToSave->getBoardData().at(j);
            }
        }

        qDebug()<<"str to save = "<<str;
        QFile file(currentFileOpened);
        QTextStream stream(&file);

        if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
             ui->statusBar->showMessage("Saving failed", 1500);
             return;
        }

        stream << str;
        stream.flush();
        file.close();

        ui->statusBar->showMessage("Board saved to file " + currentFileOpened, 1500);
    }

    else {}

    sizeWasChanged = false;

    qDebug()<<countFilesSaved;
}

void MainWindow::on_actionDownload_Pixels_triggered()
{
    if (!countFilesSaved)
    {
        ui->statusBar->showMessage("No file saved", 1500);
        return;
    }

    currentFileOpened = QFileDialog::getOpenFileName(0, "Download pixels", ".", "myboard*.txt");

    if (!QFile::exists(currentFileOpened))
    {
        ui->statusBar->showMessage("No file", 1500);
        return;
    }

    QFile file(currentFileOpened);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
         ui->statusBar->showMessage("Downloading failed", 1500);
         return;
    }

    sizeWasChanged = false;

    QString str = file.readAll();
    file.close();

    qDebug()<<"str to download = "<<str;

    m_view->deleteBoards();


    QString::iterator it = str.begin();

    //reading size of saved board from the string

    QString strLayers;
    while (*it!='\n')
    {
        strLayers+=*it;
        ++it;
    }
    int layers = strLayers.toInt();
    qDebug()<<"layers = "<<layers;

    ++it; //from '\n' to next
    QString strRanks;
    while (*it!='\n')
    {
        strRanks+=*it;
        ++it;
    }
    int ranks = strRanks.toInt();
    qDebug()<<"ranks = "<<ranks;

    ++it;
    QString strColumns;
    while (*it!='\n')
    {
        strColumns+=*it;
        ++it;
    }
    int columns = strColumns.toInt();
    qDebug()<<"columns = "<<columns;

    ++it; //now we're ready to read pixels

    for (int lay = 0; lay<layers; lay++)
    {
        MyBoard* currentBoard = m_view->AddBoard(ranks, columns);

        for (int ran = 0; ran<ranks; ran++)
        {
            for (int col = 0; col<columns; col++)
            {
                currentBoard->setChar((*it).toLatin1(), ran*columns+col);
                ++it;
            }
        }
    }

    m_view->setCurrentLayer(0);
    setFirstRankColumnToShowSlot(0,0);
    m_view->SetScale(ranks, columns);

    ui->statusBar->showMessage("Board downloaded", 1500);
}

void MainWindow::on_actionReset_Pixels_triggered()
{
    QMessageBox messageBox;
    messageBox.setText("Are you sure?");
    messageBox.setWindowTitle("Reset pixels");
    messageBox.setWindowIcon(QIcon(":/icons/refresh.png"));
    messageBox.setIconPixmap(QPixmap(":/icons/refresh.png"));
    QPushButton* yesButton = messageBox.addButton(QMessageBox::Yes);
    QPushButton* yesToAllButton = messageBox.addButton(QMessageBox::YesToAll);
    QPushButton* noButton = messageBox.addButton(QMessageBox::No);
    messageBox.exec();
    
    if(messageBox.clickedButton()==noButton) {  return; }
    
    if(messageBox.clickedButton()==yesButton)
    {
        qDebug()<<"Yes";

        m_view->getMyBoards().at(m_view->getCurrentLayer())->resetBoard();
        m_view->repaint();

        QString layerStr;
        layerStr.setNum(m_view->getCurrentLayer()+1);
        ui->statusBar->showMessage("Pixels on layer" + layerStr + " reset", 1500);
        return;
    }

    if(messageBox.clickedButton()==yesToAllButton)
    {
        qDebug()<<"YesToAll";
        
        for (MyBoard* board: m_view->getMyBoards())
        {
            board->resetBoard();
        }

        setFirstRankColumnToShowSlot(0,0);

        m_view->repaint();

        ui->statusBar->showMessage("Pixels on all layers reset", 1500);
        return;
    }    
}

void MainWindow::on_actionSet_Board_Size_triggered()
{
    qDebug()<<"Set pixels works";

    int ranks = QInputDialog::getInt(this, "Ranks", "Set number of ranks: ",
                                        m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks(), 1, m_view->height());
    int columns = QInputDialog::getInt(this, "Columns", "Set number of columns: ",
                                        m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns(), 1, m_view->width());
    int layers = QInputDialog::getInt(this, "Layers", "Set number of layers: ",
                                        m_view->getMyBoards().size(), 1, 1000);

    m_view->deleteBoards();

    for (int lay = 0; lay<layers; lay++)
    {
        m_view->AddBoard(ranks, columns);
    }

    qDebug()<<"r = "<<ranks;
    qDebug()<<"c = "<<columns;
    int maxRank = ranks - ranksToShow + 1 > 1 ?
                ranks - ranksToShow + 1
              : 1;
    ui->verticalSlider->setMaximum(maxRank);

    int maxColumn = columns - columnsToShow + 1 > 1 ?
                columns - columnsToShow + 1
              : 1;
    ui->horizontalSlider->setMaximum(maxColumn);

    if(ranks<=ranksToShow)
    {
        ui->verticalSlider->setEnabled(false);
        ui->up20Button->setEnabled(false);
        ui->upButton->setEnabled(false);
        ui->down20Button->setEnabled(false);
        ui->downButton->setEnabled(false);
    }
    else
    {
        ui->verticalSlider->setEnabled(true);
        ui->up20Button->setEnabled(true);
        ui->upButton->setEnabled(true);
        ui->down20Button->setEnabled(true);
        ui->downButton->setEnabled(true);
    }

    if (columns<=columnsToShow)
    {
        ui->horizontalSlider->setEnabled(false);
        ui->rightButton->setEnabled(false);
        ui->right20Button->setEnabled(false);
        ui->left20Button->setEnabled(false);
        ui->leftButton->setEnabled(false);
    }
    else
    {
        ui->horizontalSlider->setEnabled(true);
        ui->rightButton->setEnabled(true);
        ui->right20Button->setEnabled(true);
        ui->left20Button->setEnabled(true);
        ui->leftButton->setEnabled(true);
    }

    if (ranks<=ranksToShow && columns<=columnsToShow)
    {
        ui->topleft_Button->setEnabled(false);
    }
    else
    {
        ui->topleft_Button->setEnabled(true);
    }

    m_view->setCurrentLayer(0);
    setFirstRankColumnToShowSlot(0,0);

    m_view->SetScale(ranks, columns);

    ui->statusBar->showMessage("Board size changed", 1500);

    sizeWasChanged = true;

}

void MainWindow::on_actionCalculate_Probability_triggered()
{
    qDebug()<<"Calculate slot works";

    if (!countFilesSaved)
    {
        ui->statusBar->showMessage("No file saved", 1500);
        return;
    }

    //memorize the current situation on board
    QString currentString ="";
    for (MyBoard* board: m_view->getMyBoards())
    {
        for(char currentChar: board->getBoardData())
        {
            currentString+=currentChar;
        }
    }

    //creating list of samples
    QList<QString> myList;

    //filling it (until we say it's enough)
    while (true)
    {
        QString fileOpened = QFileDialog::getOpenFileName(0, "Download pixels", ".", "myboard*.txt");

        if (fileOpened.isEmpty()) //no file selected
        {
            break;
        }

        if (!QFile::exists(fileOpened))
        {
            ui->statusBar->showMessage("No file", 1500);
            continue;
        }

        QFile file(fileOpened);
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            ui->statusBar->showMessage("Downloading failed", 1500);
            continue;
        }

        QString tmpString = file.readAll();
        file.close();

        //pass by symbols that represent size
        auto it = tmpString.begin();
//        while ((*it).toLatin1() != 'P' && (*it).toLatin1() != ' ') {
        while (*it != QChar('P') && *it != QChar(' ')) {

             qDebug()<<(*it).toLatin1();
            ++it; }

        qDebug()<<"strings to compare begins with "<<*it;

        QString compareStr;

        while (it!=tmpString.end())
        {
            compareStr += *it;
            ++it;
        }


        if (compareStr.isEmpty() == false)
        {
            myList.push_back(compareStr);
        }

        if (QMessageBox::question(this, "Add more files", "Do you want to add more files?", QMessageBox::Yes|QMessageBox::No)
                == QMessageBox::No)
        {
            break;
        }
    }

    //calculating
    double probability = MyAlgorithm::computeProbability(myList, currentString);

    if (probability==-1) //returns if different length of strings
    {
        QMessageBox::warning(this, "Probability is not calculated", "Different length of strings!", QMessageBox::Ok);
        return;
    }

    if (probability==-2) //returnes if nothing to compare
    {
        QMessageBox::warning(this, "Probability is not calculated", "Nothing to compare!", QMessageBox::Ok);
        return;
    }
    QString probabilityString;
    probabilityString.setNum(probability*100);  //percentage

    QMessageBox::information(this, "Probability calculated", "Probability is "+probabilityString+"%", QMessageBox::Ok);


}

void MainWindow::on_actionChoose_Layer_triggered()
{
    m_view->setCurrentLayer(QInputDialog::getInt(this, "Layers", "Choose layer: ",
                                        m_view->getCurrentLayer()+1, 1, m_view->getMyBoards().size())-1);
    emit m_view->layerChangedSignal(m_view->getCurrentLayer()+1);

    setFirstRankColumnToShowSlot(0,0);
    m_view->repaint();
}

void MainWindow::on_actionAdd_Layer_triggered()
{
    //TBD
    ui->statusBar->showMessage("Adding layers coming soon...", 5000);

}

void MainWindow::on_actionDelete_Layer_triggered()
{
    //TBD
    ui->statusBar->showMessage("Deleting layers coming soon...", 5000);
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    int rank = value - 1;
    rank = rank<0? 0:rank;
    rank = rank > m_view->getMyBoards().at(0)->getRanks() - ranksToShow?
                m_view->getMyBoards().at(0)->getRanks() - ranksToShow
              : rank;
    setFirstRankColumnToShowSlot(rank, m_view->getFirstColumnToShow());
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    int column = value-1;
    column = column<0? 0:column;
    column = column > m_view->getMyBoards().at(0)->getColumns() - columnsToShow?
                m_view->getMyBoards().at(0)->getColumns() - columnsToShow
              :column;
    setFirstRankColumnToShowSlot(m_view->getFirstRankToShow(), column);
}

void MainWindow::on_left20Button_clicked()
{
    int column = m_view->getFirstColumnToShow() - columnsToShow;
    column = column<0? 0:column;
    setFirstRankColumnToShowSlot(m_view->getFirstRankToShow(), column);
}

void MainWindow::on_leftButton_clicked()
{
    int column = m_view->getFirstColumnToShow() - 1;
    column = column<0? 0:column;
    setFirstRankColumnToShowSlot(m_view->getFirstRankToShow(), column);
}

void MainWindow::on_up20Button_clicked()
{
    int rank = m_view->getFirstRankToShow() - ranksToShow;
    rank = rank<0? 0:rank;
    setFirstRankColumnToShowSlot(rank, m_view->getFirstColumnToShow());
}

void MainWindow::on_upButton_clicked()
{
    int rank = m_view->getFirstRankToShow() - 1;
    rank = rank<0? 0:rank;
    setFirstRankColumnToShowSlot(rank, m_view->getFirstColumnToShow());
}

void MainWindow::on_right20Button_clicked()
{
    int column = m_view->getFirstColumnToShow() + columnsToShow;
    column = column > m_view->getMyBoards().at(0)->getColumns() - columnsToShow?
                m_view->getMyBoards().at(0)->getColumns() - columnsToShow
              :column;
    setFirstRankColumnToShowSlot(m_view->getFirstRankToShow(), column);
}

void MainWindow::on_rightButton_clicked()
{
    int column = m_view->getFirstColumnToShow() + 1;
    column = column > m_view->getMyBoards().at(0)->getColumns() - columnsToShow?
                m_view->getMyBoards().at(0)->getColumns() - columnsToShow
                :column;
    setFirstRankColumnToShowSlot(m_view->getFirstRankToShow(), column);
}

void MainWindow::on_down20Button_clicked()
{
    int rank = m_view->getFirstRankToShow() + ranksToShow;
    rank = rank > m_view->getMyBoards().at(0)->getRanks() - ranksToShow?
                m_view->getMyBoards().at(0)->getRanks() - ranksToShow
              : rank;

    setFirstRankColumnToShowSlot(rank, m_view->getFirstColumnToShow());
}

void MainWindow::on_downButton_clicked()
{
    int rank = m_view->getFirstRankToShow() + 1;
    rank = rank > m_view->getMyBoards().at(0)->getRanks() - ranksToShow?
                m_view->getMyBoards().at(0)->getRanks() - ranksToShow
              : rank;

    setFirstRankColumnToShowSlot(rank, m_view->getFirstColumnToShow());
}

void MainWindow::on_topleft_Button_clicked()
{
    setFirstRankColumnToShowSlot(0,0);
}

void MainWindow::on_bottomleft_Button_clicked()
{
    int ranks = m_view->getMyBoards().at(0)->getRanks() - ranksToShow > 0?
                m_view->getMyBoards().at(0)->getRanks() - ranksToShow
              : 0;
    setFirstRankColumnToShowSlot(ranks, 0);
}

void MainWindow::on_topright_Button_clicked()
{
    int columns = m_view->getMyBoards().at(0)->getColumns() - columnsToShow > 0?
                m_view->getMyBoards().at(0)->getColumns() - columnsToShow
              : 0;
    setFirstRankColumnToShowSlot(0, columns);
}

void MainWindow::on_bottomright_Button_clicked()
{
    int ranks = m_view->getMyBoards().at(0)->getRanks() - ranksToShow > 0?
                m_view->getMyBoards().at(0)->getRanks() - ranksToShow
              : 0;
    int columns = m_view->getMyBoards().at(0)->getColumns() - columnsToShow > 0?
                m_view->getMyBoards().at(0)->getColumns() - columnsToShow
              : 0;

    setFirstRankColumnToShowSlot(ranks, columns);
}

void MainWindow::ranksColumnsToShowChangedSlot(int ranks, int columns)
{

    qDebug()<<"ranks = "<<ranks;
    QString ranksToShowString;
    ranksToShowString.setNum(ranks);
    QString columnsToShowString;
    columnsToShowString.setNum(columns);
    ui->left20Button->setText(columnsToShowString);
    ui->right20Button->setText(columnsToShowString);
    ui->down20Button->setText(ranksToShowString);
    ui->up20Button->setText(ranksToShowString);

    int maxRank = m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks() - ranks + 1 > 1?
                m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks() - ranks + 1
              : 1;
    ui->verticalSlider->setMaximum(maxRank);

    int maxColumn = m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns() - columns + 1 > 1?
                m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns() - columns + 1
              : 1;
    ui->horizontalSlider->setMaximum(maxColumn);

    ranksToShow = ranks;
    columnsToShow = columns;

    //Left buttons
    if (m_view->getFirstColumnToShow()) { ui->leftButton->setEnabled(true); ui->left20Button->setEnabled(true); }
    else { ui->leftButton->setEnabled(false); ui->left20Button->setEnabled(false); }

    //Top buttons
    if (m_view->getFirstRankToShow()) { ui->upButton->setEnabled(true); ui->up20Button->setEnabled(true);}
    else { ui->upButton->setEnabled(false); ui->upButton->setEnabled(false); }

    //Top left button
    if (m_view->getFirstColumnToShow() || m_view->getFirstRankToShow()) { ui->topleft_Button->setEnabled(true); }
    else { ui->topleft_Button->setEnabled(false);}

    //Right buttons
    if (columnsToShow + m_view->getFirstColumnToShow() < m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns())
    { ui->rightButton->setEnabled(true); ui->right20Button->setEnabled(true); }
    else { ui->rightButton->setEnabled(false); ui->right20Button->setEnabled(false); }

    //Bottom buttons
    if (ranksToShow + m_view->getFirstRankToShow() < m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks())
    { ui->downButton->setEnabled(true); ui->down20Button->setEnabled(true); }
    else { ui->downButton->setEnabled(false); ui->down20Button->setEnabled(false); }

    //Bottom right button
    if (ranksToShow + m_view->getFirstRankToShow() < m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks()
            || columnsToShow + m_view->getFirstColumnToShow() < m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns())
    { ui->bottomright_Button->setEnabled(true);}
    else { ui->bottomright_Button->setEnabled(false);}

    //Bottom left button
    if (ranksToShow + m_view->getFirstRankToShow() < m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks()
            || m_view->getFirstColumnToShow())
    { ui->bottomleft_Button->setEnabled(true); }
    else {ui->bottomleft_Button->setEnabled(false); }

    //Top right button
    if (columnsToShow + m_view->getFirstColumnToShow() < m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns()
            || m_view->getFirstRankToShow())
    { ui->topright_Button->setEnabled(true); }
    else {ui->topright_Button->setEnabled(false); }

    //horisontal slider
    if (columnsToShow < m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns())
    { ui->horizontalSlider->setEnabled(true); }
    else { ui->horizontalSlider->setEnabled(false); }

    //vertical slider
    if (ranksToShow < m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks())
    { ui->verticalSlider->setEnabled(true); }
    else {ui->verticalSlider->setEnabled(false); }
}

void MainWindow::on_actionParse_Image_triggered()
{
    qDebug()<<"Parsing image slot works";

    QString fileOpened = QFileDialog::getOpenFileName(0, "Download picture", ".", "Images (*.png *.xpm *.bmp *.tif *.jpg)");

    if (fileOpened.isEmpty()) //no file selected
    {
        return;
    }

    QImage image (fileOpened);
    QPixmap pix (fileOpened);

    qDebug()<<"before - w = "<<pix.width()<<", h = "<<pix.height();
    pix = pix.scaled(ui->picturePreviewLabel->width(), ui->picturePreviewLabel->height(), Qt::KeepAspectRatio);
    qDebug()<<"after - w = "<<pix.width()<<", h = "<<pix.height();
    ui->picturePreviewLabel->setPixmap(pix);

    QMessageBox::information(this, "Picture preview", "Downloaded picture on preview", QMessageBox::Ok);

    QImage blackWhiteImage = MyAlgorithm::coloredToBlackWhite(image/*, 100*/); //transferring difference value is also possible

    pix = QPixmap::fromImage(blackWhiteImage);
    pix = pix.scaled(ui->picturePreviewLabel->width(), ui->picturePreviewLabel->height(), Qt::KeepAspectRatio);
    ui->picturePreviewLabel->setPixmap(pix);

    QMessageBox::information(this, "Picture preview", "Black and white picture on preview", QMessageBox::Ok);

    blackWhiteImage = MyAlgorithm::noiseReduction(blackWhiteImage/*, 5*/); //transferring iteration value is also possible

//    QImage blackWhiteImage = ChessAlgorithm::noiseReduction_median(image/*, 11*/);

    pix = QPixmap::fromImage(blackWhiteImage);
    pix = pix.scaled(ui->picturePreviewLabel->width(), ui->picturePreviewLabel->height(), Qt::KeepAspectRatio);
    ui->picturePreviewLabel->setPixmap(pix);

    int choice = (QMessageBox::question(this, "Picture preview", "Noiseless picture on preview\nWant to show it at the main view?", QMessageBox::Yes | QMessageBox::No));

    switch  (choice)
    {
        case 0x00004000:
        {
            qDebug()<<"button = yes";

            m_view->deleteBoards();

            if (blackWhiteImage.height() > m_view->height()
                    || blackWhiteImage.width() > m_view->width())
            {
                blackWhiteImage = blackWhiteImage.scaled(m_view->width(), m_view->height(), Qt::KeepAspectRatio);
            }

            int ranks = blackWhiteImage.height();
            int columns = blackWhiteImage.width();
            m_view->AddBoard(ranks, columns);


            int maxRank = ranks - ranksToShow + 1 > 1 ?
                        ranks - ranksToShow + 1
                      : 1;
            ui->verticalSlider->setMaximum(maxRank);

            int maxColumn = columns - columnsToShow + 1 > 1 ?
                        columns - columnsToShow + 1
                      : 1;
            ui->horizontalSlider->setMaximum(maxColumn);

            if(ranks<=ranksToShow)
            {
                ui->verticalSlider->setEnabled(false);
                ui->up20Button->setEnabled(false);
                ui->upButton->setEnabled(false);
                ui->down20Button->setEnabled(false);
                ui->downButton->setEnabled(false);
            }
            else
            {
                ui->verticalSlider->setEnabled(true);
                ui->up20Button->setEnabled(true);
                ui->upButton->setEnabled(true);
                ui->down20Button->setEnabled(true);
                ui->downButton->setEnabled(true);
            }

            if (columns<=columnsToShow)
            {
                ui->horizontalSlider->setEnabled(false);
                ui->rightButton->setEnabled(false);
                ui->right20Button->setEnabled(false);
                ui->left20Button->setEnabled(false);
                ui->leftButton->setEnabled(false);
            }
            else
            {
                ui->horizontalSlider->setEnabled(true);
                ui->rightButton->setEnabled(true);
                ui->right20Button->setEnabled(true);
                ui->left20Button->setEnabled(true);
                ui->leftButton->setEnabled(true);
            }

            if (ranks<=ranksToShow && columns<=columnsToShow)
            {
                ui->topleft_Button->setEnabled(false);
            }
            else
            {
                ui->topleft_Button->setEnabled(true);
            }

            m_view->setCurrentLayer(0);
            setFirstRankColumnToShowSlot(0,0);

            for (int y = 0; y < ranks; y++)
            {
                for (int x = 0; x < columns; x++)
                {
                    if (blackWhiteImage.pixel(x, y) == qRgb(0, 0, 0))
                    {
                        m_view->getMyBoards().at(m_view->getCurrentLayer())->setChar('P', columns*y + x);
                    }
                }
            }

            m_view->SetScale(m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks(), m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns());

            ui->statusBar->showMessage("Board size changed", 1500);

            sizeWasChanged = true;
            break;
        }
        case 0x00010000: {  qDebug()<<"button = no"; break; }
        default:break;
    }


}

void MainWindow::on_fullSizeButton_clicked()
{
    m_view->SetScale(m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks(), m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   if (windowState() != oldWindowState)
    {
        qDebug()<<"main window state changed";
        m_view->SetScale(m_view->getMyBoards().at(m_view->getCurrentLayer())->getRanks(), m_view->getMyBoards().at(m_view->getCurrentLayer())->getColumns());
        oldWindowState = windowState();
    }

}
