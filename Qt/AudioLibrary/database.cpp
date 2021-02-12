#include "database.h"

DataBase::DataBase(QString const& path)
{
    this->setPathFromFile(path);
    this->listAudio = new QList<Audio*>();
    this->setDataBaseFromFile();
    this->sort(6,1);
}

DataBase::~DataBase()
{
    delete listAudio;
}

bool DataBase::findAudio(Audio * audio)
{
    QList<Audio*>* list = this->listAudio;
    for(QList<Audio*>::iterator it = list->begin(); it !=  list->end(); it++)
    {
        Audio * thisAudio = *it;
        if(thisAudio == audio)
        {
            return true;
        }
    }
    return false;
}

void DataBase::setPathFromFile(QString const& path)
{
    if(!path.isEmpty())
    {
        this->pathFromFile = path;
    }
}

QString DataBase::getPathFromFile()
{
    return this->pathFromFile;
}

QString DataBase::getInformation()
{
    QString result;
    for(QList<Audio*>::iterator it = this->listAudio->begin(); it != this->listAudio->end(); it++)
    {
        Audio * audio = *it;
        result += audio->getInformation() + "\n";
    }
    return result;
}

void DataBase::updateDataBaseFromFile()
{
    QFile file(this->pathFromFile);
    if(file.open(QIODevice::WriteOnly))
    {
        this->sort(6,1);
        QString allText = this->getInformation();
        QByteArray text = allText.toUtf8();
        file.write(text);
    }
    file.close();
}

int DataBase::addAudio(Audio * audio)
{
    if(!this->listAudio->empty())
    {
        if(this->findAudio(audio) == false)
        {
            this->listAudio->append(audio);
            this->updateDataBaseFromFile();
        }
        else {
            return -1;
        }
    }
    else {
        this->listAudio->append(audio);
        this->updateDataBaseFromFile();
    }
    return 0;
}

void DataBase::deleteAudio(Audio * audio)
{
    if(!this->listAudio->empty())
    {
        if(this->listAudio->indexOf(audio) >= 0)
        {
            this->listAudio->removeOne(audio);
            this->updateDataBaseFromFile();
        }
    }

}

QList<Audio*>* DataBase::getListAudio()
{
    return this->listAudio;
}

void DataBase::setDataBaseFromFile()
{
    QString text;
    QFile file(this->pathFromFile);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QByteArray line = file.readAll();
            text = line;
        }
        file.close();
    }
    QStringList line = text.split("\n");
    for(int i = 0; i < line.length(); i++)
    {
        Audio * audio;
        QStringList textAudio = line[i].split("|");
        if(!textAudio[0].isEmpty())
        {
            if(QFileInfo::exists(textAudio[2]))
            {
                if(textAudio[0] == "Музыка")
                {
                    audio = new Music(textAudio[1], textAudio[2],  QDateTime::fromString(textAudio[3],"dd.MM.yyyy"), textAudio[4], textAudio[5],
                                              textAudio[6], QTime::fromString(textAudio[7],"hh:mm:ss"), textAudio[8]);
                    this->listAudio->append(audio);

                }
                if(textAudio[0] == "Аудиокнига")
                {
                    audio = new AudioBook(textAudio[1], textAudio[2], QDateTime::fromString(textAudio[3],"dd.MM.yyyy"), textAudio[4], textAudio[5],
                            textAudio[6], QTime::fromString(textAudio[7],"hh:mm:ss"), textAudio[8]);
                    this->listAudio->append(audio);

                }
            }
        }
    }
}

void DataBase::editAudio(Audio * audio, Audio * editAudio)
{
    if(!this->listAudio->empty())
    {
        int index = this->listAudio->indexOf(audio);
        if(index >= 0)
        {
            this->listAudio->replace(index, editAudio);
            this->updateDataBaseFromFile();
        }
    }
}

QList<Audio*>* DataBase::searchString(QString inputData)
{
    QList<Audio*>* searched = new QList<Audio*>();
    for(QList<Audio*>::iterator it = this->listAudio->begin(); it !=  this->listAudio->end(); it++)
    {
        Audio * audio = *it;
        if(audio->getInformation().contains(inputData))
        {
            searched->append(audio);
        }
    }
    return searched;
}

void DataBase::sort(int index, int status)
{
    if(status == 1)
    {
        if(index == 0)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getName() < b->getName(); });
        }
        if(index == 1)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getPerformer() < b->getPerformer(); });
        }
        if(index == 5)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getDuration() < b->getDuration(); });
        }
        if(index == 6)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getDateAdded() < b->getDateAdded(); });
        }
    }
    else
    {
        if(index == 0)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getName() > b->getName(); });
        }
        if(index == 1)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getPerformer() > b->getPerformer(); });
        }
        if(index == 5)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getDuration() > b->getDuration(); });
        }
        if(index == 6)
        {
           qSort(this->listAudio->begin(), this->listAudio->end(),[](Audio* a, Audio* b) { return a->getDateAdded() > b->getDateAdded(); });
        }
    }
}
