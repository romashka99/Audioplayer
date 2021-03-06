#pragma
#ifndef AUDIOBOOK_H
#define AUDIOBOOK_H

#include "audio.h"


class AUDIOLIBSHARED_EXPORT AudioBook : public Audio
{
private:
    QString autor;
public:
    AudioBook(QString const& name, QString const& path, QDateTime const& date, QString const& language,
              QString const& performer, QString const& genre, QTime const& time, QString const& autor);
    void setAutor(QString const& autor);
    QString getAutor();
    QString getInformation() override;
    QString getFeature() override;
    AudioBook & operator=(AudioBook & audiobook);
};

#endif // AUDIOBOOK_H
