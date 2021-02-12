#include "audiobook.h"

AudioBook::AudioBook(QString const& name, QString const& path, QDateTime const& date, QString const& language,
                     QString const& performer, QString const& genre, QTime const& time, QString const& autor)
    : Audio(name, path, date, language, performer, genre, time)
{
    this->setAutor(autor);
}

void AudioBook::setAutor(QString const& autor)
{
    this->autor = autor;
}

QString AudioBook::getAutor()
{
    return this->autor;
}

QString AudioBook::getInformation()
{
    return "Музыка|" + this->getName() + "|" + this->getPath() + "|" + this->getDateAdded().toString("dd.MM.yyyy")
            + "|" + this->getLanguage() + "|" + this->getPerformer() + "|" + this->getGenre() + "|"
            + this->getDuration().toString("hh:mm:ss") + "|" + this->getAutor();
}

QString AudioBook::getFeature()
{
    return this->getAutor();
}

QString AudioBook::getCategory()
{
    return "Аудиокнига";
}

