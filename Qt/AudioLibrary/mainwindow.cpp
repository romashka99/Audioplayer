#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dataBase = new DataBase(QString(QDir::currentPath() + "/DataBase.txt"));

    ui->listAudio->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listAudio->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listAudio->setSelectionMode(QAbstractItemView::SingleSelection);

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(player);
    player->setPlaylist(playlist);
    player->setVolume(30);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    this->setTableData(dataBase->getListAudio());

    connect(ui->addAudio, SIGNAL(triggered()), this, SLOT(on_addAudio()));
    connect(ui->btn_add, SIGNAL(clicked()), this, SLOT(on_addAudio()));
    connect(ui->btn_delete, SIGNAL(clicked()), this, SLOT(on_deleteAudio_triggered()));
    connect(ui->btn_previous, SIGNAL(clicked()), this, SLOT(on_previous()));
    connect(ui->previousAudio, SIGNAL(triggered()), this, SLOT(on_previous()));
    connect(ui->btn_next, SIGNAL(clicked()), this, SLOT(on_next()));
    connect(ui->nextAudio, SIGNAL(triggered()), this, SLOT(on_next()));
    connect(ui->btn_play, SIGNAL(clicked()), this, SLOT(on_play()));
    connect(ui->playAudio, SIGNAL(triggered()), this, SLOT(on_play()));
    connect(ui->btn_pause, SIGNAL(clicked()), this, SLOT(on_pause()));
    connect(ui->pauseAudio, SIGNAL(triggered()), this, SLOT(on_pause()));
    connect(ui->btn_stop, SIGNAL(clicked()), this, SLOT(on_stop()));
    connect(ui->stopAudio, SIGNAL(triggered()), this, SLOT(on_stop()));
    connect(this->player, SIGNAL(positionChanged(qint64)), this, SLOT(positionAudio(qint64)));
    connect(this->playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(switching(int)));
    connect(ui->listAudio->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));
    connect(this->player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(changedStatus(QMediaPlayer::MediaStatus)));
}

void MainWindow::setTableData(QList<Audio*> *currentList)
{
    playlist->clear();
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    QStringList horizontalHeader;
    horizontalHeader.append("Наименование");
    horizontalHeader.append("Исполнитель");
    horizontalHeader.append("Жанр");
    horizontalHeader.append("Альбом/Автор");
    horizontalHeader.append("Язык");
    horizontalHeader.append("Время");
    horizontalHeader.append("Дата добавления");

    model->setHorizontalHeaderLabels(horizontalHeader);

    int i = 0;

    for(QList<Audio*>::iterator it = currentList->begin(); it !=  currentList->end(); it++)
    {
        Audio * audio = *it;
        playlist->addMedia(QUrl(audio->getPath()));

        item = new QStandardItem(audio->getName());
        model->setItem(i,0,item);

        item = new QStandardItem(audio->getPerformer());
        model->setItem(i,1,item);

        item = new QStandardItem(audio->getGenre());
        model->setItem(i,2,item);

        item = new QStandardItem(audio->getFeature());
        model->setItem(i,3,item);

        item = new QStandardItem(audio->getLanguage());
        model->setItem(i,4,item);

        item = new QStandardItem(audio->getDuration().toString("hh:mm:ss"));
        model->setItem(i,5,item);

        item = new QStandardItem(audio->getDateAdded().toString("dd.MM.yyyy"));
        model->setItem(i,6,item);
        i++;
    }

    ui->listAudio->setModel(model);

    ui->listAudio->resizeRowsToContents();
    ui->listAudio->resizeColumnsToContents();
}

void MainWindow::setCurrentName()
{
    this->currentName = ui->listAudio->model()->data(ui->listAudio->model()->index(this->currentIndex.row(), 0)).toString();
    ui->currentAudio->setText(this->currentName);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete playlist;
    delete player;
    delete dataBase;
}

void MainWindow::on_addAudio()
{
    AudioForm * form = new AudioForm(this);
    form->setModal(true);
    if(form->exec() == QDialog::Accepted)
    {
        if(dataBase->addAudio(form->audio) == 0)
        {
            this->setTableData(dataBase->getListAudio());
            warning.setWindowTitle(this->windowTitle());
            warning.setText("Аудио добавлено.");
            warning.setIcon(QMessageBox::Information);
            warning.exec();
        }
        else
        {
            this->setTableData(dataBase->getListAudio());
            warning.setWindowTitle(this->windowTitle());
            warning.setText("Такая аудиозапись уже существует.");
            warning.setIcon(QMessageBox::Warning);
            warning.exec();
        }
    }

}

void MainWindow::on_editAudio_triggered()
{
    QModelIndex indexTable = ui->listAudio->currentIndex();
    if(indexTable.row() < 0)
    {
        warning.setWindowTitle(this->windowTitle());
        warning.setText("Аудио не выбрано.");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }
    else
    {
        QList<Audio*>* list = dataBase->getListAudio();
        for(QList<Audio*>::iterator it = list->begin(); it !=  list->end(); it++)
        {
            Audio * audio = *it;
            if(audio->getName() == this->currentName)
            {
                AudioForm * form = new AudioForm(audio,this);
                form->setModal(true);
                if(form->exec() == QDialog::Accepted)
                {
                    this->dataBase->editAudio(audio, form->audio);
                    this->setTableData(dataBase->getListAudio());
                    warning.setWindowTitle(this->windowTitle());
                    warning.setText("Аудио изменено.");
                    warning.setIcon(QMessageBox::Information);
                    warning.exec();
                    return;
                }
            }
        }
    }
}

void MainWindow::on_deleteAudio_triggered()
{
    QModelIndex indexTable = ui->listAudio->currentIndex();
    if(indexTable.row() < 0)
    {
        warning.setWindowTitle(this->windowTitle());
        warning.setText("Аудио не выбрано.");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }
    else
    {
        QMessageBox deleteMessage;
        deleteMessage.setWindowTitle(this->windowTitle());
        deleteMessage.setText("Вы действительно хотите удалить это аудио?");
        deleteMessage.setIcon(QMessageBox::	Question);
        deleteMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        deleteMessage.setDefaultButton(QMessageBox::No);
        if(deleteMessage.exec() == QMessageBox::Yes)
        {
            QList<Audio*>* list = dataBase->getListAudio();
            for(QList<Audio*>::iterator it = list->begin(); it !=  list->end(); it++)
            {
                Audio * audio = *it;
                if(audio->getName() == this->currentName)
                {
                    this->dataBase->deleteAudio(audio);
                    this->setTableData(dataBase->getListAudio());
                    warning.setWindowTitle(this->windowTitle());
                    warning.setText("Аудио удалено.");
                    warning.setIcon(QMessageBox::Information);
                    warning.exec();
                    return;
                }

            }
        }
    }

}

void MainWindow::on_previous()
{
    this->playlist->previous();
    this->currentIndex = ui->listAudio->currentIndex();
    this->setCurrentName();
}

void MainWindow::on_next()
{
    this->playlist->next();
    this->currentIndex = ui->listAudio->currentIndex();
    this->setCurrentName();
}

void MainWindow::on_play()
{
    if(this->currentIndex.row() != -1)
    {
        if(this->playlist->currentIndex() == this->currentIndex.row())
        {
            this->player->play();
        }
        else
        {
            while(this->playlist->currentIndex() != this->currentIndex.row())
            {
                this->playlist->next();
            }
        }
    }
    else
    {
        this->player->play();
    }
    int duration = int(this->player->duration());

    ui->slider_durationAudio->setMaximum(duration);
    this->setCurrentName();
}

void MainWindow::on_pause()
{
   this->player->pause();
}

void MainWindow::on_stop()
{
   this->player->stop();
   ui->currentAudio->clear();
}

void MainWindow::on_listAudio_doubleClicked(const QModelIndex &index)
{
    this->currentIndex = index;
    this->on_play();
}


void MainWindow::switching(int index)
{
    ui->listAudio->selectRow(index);
}

void MainWindow::on_slider_volume_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_btn_volume_clicked()
{
    this->statusVolume *= -1;
    if(this->statusVolume == -1)
    {
        player->setVolume(0);
        ui->slider_volume->setValue(0);
    }
    else
    {
        player->setVolume(30);
        ui->slider_volume->setValue(30);
    }
}

void MainWindow::positionAudio(qint64 value)
{
    ui->slider_durationAudio->setValue(int(value));
}

void MainWindow::on_slider_durationAudio_sliderMoved(int position)
{
    this->player->setPosition(position);
}

void MainWindow::on_listAudio_clicked(const QModelIndex &index)
{
    this->currentIndex = index;
    this->setCurrentName();
}

void MainWindow::sortByColumn(int indexColumn)
{
    this->statusSort *= -1;
    this->dataBase->sort(indexColumn, this->statusSort);
    this->setTableData(this->dataBase->getListAudio());
}


void MainWindow::on_searchAudio_triggered()
{
    ui->editSearch->clear();
    this->setTableData(this->dataBase->getListAudio());
}

void MainWindow::on_btn_search_clicked()
{
    this->setTableData(this->dataBase->searchString(ui->editSearch->text()));
}

void MainWindow::changedStatus(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia)
    {
        this->duration = int(player->duration());
    }
}
