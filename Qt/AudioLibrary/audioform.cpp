#include "audioform.h"
#include "ui_audioform.h"

QStringList setGenre(QString category)
{
    QStringList genre = QStringList();
    if(category == "Музыкальная запись")
    {
        genre << "Блюз" << "Рок" << "Джаз" << "Реп" << "Кантри" << "Классическая музыка" << "Мюзикл" << "Народная песня" << "Опера"
              << "Панк-рок" << "Поп-музыка" << "Рок-н-ролл" << "Хип-хоп" << "Шансон";
    }
    else
    {
        genre << "Фантастика" << "Роман, проза" << "Детективы, триллеры" << "Классика" << "Психология, философия" << "Ужасы, мистика"
              << "Аудиоспектакли" << "Приключения" << "История" << "Эзотерика" << "Бизнес" << "Научно-популярное" << "Детские аудиокниги"
              << "Юмор, сатира" << "Обучение" << "Ранобэ" << "Биографии, мемуары" << "На иностранных языках" << "Поэзия" << "Религия"
              << "Путешествия" << "Разное";
    }
    return genre;

}

QTime setTime(int ms)
{
    QTime *time = new QTime(0,0);
    return time->addMSecs(ms);
}

AudioForm::AudioForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AudioForm)
{
    ui->setupUi(this);
    this->player = new QMediaPlayer(this);
    this->setWindowTitle("Добавить аудио");
    ui->comboBoxGenre->addItems(setGenre(ui->comboBoxCategory->currentText()));
    connect(this->player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(changedStatus(QMediaPlayer::MediaStatus)));
}

AudioForm::AudioForm(Audio * audio, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AudioForm)
{
    ui->setupUi(this);
    this->setWindowTitle("Изменить аудио");
    durationEditAudio = audio->getDuration();
    ui->comboBoxGenre->addItems(setGenre(audio->getCategory()));
    ui->comboBoxCategory->setCurrentText(audio->getCategory());
    ui->comboBoxGenre->setCurrentText(audio->getGenre());
    ui->lineEditName->setText(audio->getName());
    ui->lineEditPath->setText(audio->getPath());
    ui->lineEditPerformer->setText(audio->getPerformer());
    ui->comboBoxLenguage->setCurrentText(audio->getLanguage());
    ui->lineEditAlbum->setText(audio->getFeature());
    if(audio->getCategory() == "Музыкальная запись")
    {
        ui->labelAlbum->setText("Альбом:");
    }
    else
    {
        ui->labelAlbum->setText("Автор:");
    }
}

bool AudioForm::validated()
{
    if(ui->lineEditName->text().isEmpty() || ui->lineEditAlbum->text().isEmpty() || ui->lineEditPerformer->text().isEmpty()
            || ui->comboBoxLenguage->currentText().isEmpty() || ui->lineEditPath->text().isEmpty())
    {
        return false;
    }
    return true;
}

bool AudioForm::validatedFormatFile()
{
    QFileInfo audioFile(ui->lineEditPath->text());
    if(audioFile.suffix() == "mp3")
    {
        return true;
    }
    return false;
}

bool AudioForm::audiofileExist()
{
    if(QFileInfo::exists(ui->lineEditPath->text()))
    {
        return true;
    }
    return false;
}

AudioForm::~AudioForm()
{
    delete ui;
    delete player;
}

void AudioForm::on_comboBoxCategory_currentIndexChanged(int index)
{
    ui->comboBoxGenre->clear();
    if(index == 0)
    {
        ui->labelAlbum->setText("Альбом:");
    }
    if(index == 1)
    {
        ui->labelAlbum->setText("Автор:");
    }
    ui->comboBoxGenre->addItems(setGenre(ui->comboBoxCategory->currentText()));
}

void AudioForm::on_pushButtonOK_clicked()
{
    if(this->validated() == true)
    {
        this->setResult(QDialog::Accepted);
        QTime duration;
        if(this->windowTitle() == "Добавить аудио")
        {
            duration = setTime(this->duration);
        }
        else
        {
            duration = this->durationEditAudio;
        }
        if(ui->comboBoxCategory->currentIndex() == 0)
        {
            audio = new Music(ui->lineEditName->text(), ui->lineEditPath->text(),QDateTime::currentDateTime(),
                              ui->comboBoxLenguage->currentText(), ui->lineEditPerformer->text(), ui->comboBoxGenre->currentText(),
                              duration, ui->lineEditAlbum->text());
        }
        if(ui->comboBoxCategory->currentIndex() == 1)
        {
            audio = new AudioBook(ui->lineEditName->text(), ui->lineEditPath->text(),QDateTime::currentDateTime(),
                                  ui->comboBoxLenguage->currentText(), ui->lineEditPerformer->text(), ui->comboBoxGenre->currentText(),
                                  duration, ui->lineEditAlbum->text());
        }
        this->done(1);
    }
    else
    {
        QMessageBox warning;
        warning.setWindowTitle(this->windowTitle());
        warning.setText("Заполнены не все поля, либо поля введены некорректно!");
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
    }
}

void AudioForm::on_pushButtonCancel_clicked()
{
    this->close();
}

void AudioForm::on_pushButtonPath_clicked()
{
    QString pathFolder = QDir::currentPath() + "/playlist";
    QString path = QFileDialog::getOpenFileName(this, "Выберите аудиофайл", pathFolder, "*.mp3");
    if(path.isEmpty() == false)
    {
        ui->lineEditPath->setText(path);
        player->setMedia(QUrl(ui->lineEditPath->text()));
    }
}

void AudioForm::on_lineEditPath_editingFinished()
{
    if(ui->lineEditPath->text().isEmpty() == false)
    {
        QMessageBox warning;
        if(this->audiofileExist() == false)
        {
            warning.setWindowTitle(this->windowTitle());
            warning.setText("Такого файла не существует!");
            warning.setIcon(QMessageBox::Critical);
            warning.exec();
            ui->lineEditPath->setFocus();
        }
        else
        {
            if(this->validatedFormatFile() == false)
            {
                warning.setWindowTitle(this->windowTitle());
                warning.setText("Формат файла не язвляется форматом аудиофайла!");
                warning.setIcon(QMessageBox::Critical);
                warning.exec();
                ui->lineEditPath->setFocus();
            }
            else
            {
                player->setMedia(QUrl(ui->lineEditPath->text()));
            }
        }
    }
}

void AudioForm::changedStatus(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia)
    {
        this->duration = int(player->duration());
    }
}
