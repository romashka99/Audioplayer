#include "music.h"

Music::Music(QString const& name, QString const& path, QDateTime const& date, QString const& language,
             QString const& performer, QString const& genre, QTime const& time, QString const& album)
    : Audio(name, path, date, language, performer, genre, time)
{
    this->setAlbum(album);
}

void Music::setAlbum(QString const& album)
{
    this->album = album;
}

QString Music::getAlbum()
{
    return this->album;
}

QString Music::getInformation()
{
    return "Музыка|" + this->getName() + "|" + this->getPath() + "|" + this->getDateAdded().toString("dd.MM.yyyy")
            + "|" + this->getLanguage() + "|" + this->getPerformer() + "|" + this->getGenre() + "|"
            + this->getDuration().toString("hh:mm:ss") + "|" + this->getAlbum();
}

QString Music::getFeature()
{
    return this->getAlbum();
}

QString Music::getCategory()
{
    return "Музыкальная запись";
}

