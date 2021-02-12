#ifndef AUDIOFORM_H
#define AUDIOFORM_H

#include <QDialog>
#include <QAbstractButton>
#include "audiobook.h"
#include "music.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaPlayer>

namespace Ui {
class AudioForm;
}

class AudioForm : public QDialog
{
    Q_OBJECT

private:
    int duration = 0;
    QMediaPlayer * player;
    QTime durationEditAudio;
public:
    Audio * audio;
    explicit AudioForm(QWidget *parent = nullptr);
    explicit AudioForm(Audio * audio, QWidget *parent = nullptr);
    bool validated();
    bool validatedFormatFile();
    bool audiofileExist();
    ~AudioForm();

private slots:
    void on_comboBoxCategory_currentIndexChanged(int index);

    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonPath_clicked();

    void on_lineEditPath_editingFinished();

    void changedStatus(QMediaPlayer::MediaStatus status);

private:
    Ui::AudioForm *ui;
};

#endif // AUDIOFORM_H
