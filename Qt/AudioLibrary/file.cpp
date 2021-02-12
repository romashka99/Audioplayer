#include "file.h"

File::File(QString const& name, QString const& path, QDateTime const& date, QString const& language) : Product(name)
{
    this->setPath(path);
    this->setDateAdded(date);
    this->setLanguage(language);
}

void File::setPath(QString const& path)
{
    this->path = path;
}

QString File::getPath()
{
    return this->path;
}

void File::setDateAdded(QDateTime const& date)
{
    this->dateAdded = date;
}

QDateTime File::getDateAdded()
{
    return this->dateAdded;
}

void File::setLanguage(QString const& language)
{
    this->language = language;
}

QString File::getLanguage()
{
    return this->language;
}
