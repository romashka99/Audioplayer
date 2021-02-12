#include "audio.h"

Audio::Audio(QString const& name, QString const& path, QDateTime const& date, QString const& language,
             QString const& performer, QString const& genre, QTime const& time)
    : File(name, path, date, language)
{
    this->setPerformer(performer);
    this->setGenre(genre);
    this->setDuration(time);
}

void Audio::setPerformer(QString const& performer)
{
    this->performer = performer;
}

QString Audio::getPerformer()
{
    return this->performer;
}

void Audio::setGenre(QString const& genre)
{
    this->genre = genre;
}

QString Audio::getGenre()
{
    return this->genre;
}

void Audio::setDuration(QTime const& time)
{
    this->duration = time;
}

QTime Audio::getDuration()
{
    return this->duration;
}

bool Audio::operator==(Audio & audio)
{
    if(this->getName() == audio.getName() || this->getPath() == audio.getPath())
    {
        return true;
    }
    return false;
}




