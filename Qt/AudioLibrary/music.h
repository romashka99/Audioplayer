#pragma
#ifndef MUSIC_H
#define MUSIC_H

#include "audio.h"

class Music : public Audio
{
private:
    QString album;
public:
    Music(QString const& name, QString const& path, QDateTime const& date, QString const& language,
          QString const& performer, QString const& genre, QTime const& time, QString const& album);
    void setAlbum(QString const& album);
    QString getAlbum();
    QString getInformation() override;
    QString getFeature() override;
    QString getCategory() override;
};

#endif // MUSIC_H
