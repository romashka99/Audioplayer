#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "audioform.h"
#include "database.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    DataBase *dataBase;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    int statusVolume = 1;
    int statusSort = -1;
    QMessageBox warning;
    QModelIndex currentIndex;
    QString currentName;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setTableData(QList<Audio*> * currentList);
    void setCurrentName();
private slots:

    void on_addAudio();

    void on_editAudio_triggered();

    void on_deleteAudio_triggered();

    void switching(int index);

    void on_previous();

    void on_next();

    void on_play();

    void on_pause();

    void on_stop();

    void on_listAudio_doubleClicked(const QModelIndex &index);

    void on_slider_volume_valueChanged(int value);

    void on_btn_volume_clicked();

    void positionAudio(qint64);

    void on_slider_durationAudio_sliderMoved(int position);

    void on_listAudio_clicked(const QModelIndex &index);

    void sortByColumn(int indexColumn);

    void on_searchAudio_triggered();

    void on_btn_search_clicked();

    void changedStatus(QMediaPlayer::MediaStatus status);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
