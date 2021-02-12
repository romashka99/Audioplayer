#pragma
#ifndef AUDIO_H
#define AUDIO_H
#include "file.h"

class Audio : public File
{
private:
    QString performer;
    QString genre;
    QTime duration;
public:
    Audio(QString const& name, QString const& path, QDateTime const& date, QString const& language,
          QString const& performer, QString const& genre, QTime const& time);
    void setPerformer(QString const& performer);
    QString getPerformer();
    void setGenre(QString const& genre);
    QString getGenre();
    void setDuration(QTime const& time);
    QTime getDuration();
    virtual QString getCategory() = 0;
    virtual QString getInformation() = 0;
    virtual QString getFeature() = 0;
    bool operator==(Audio & audio);
};

#endif // AUDIO_H
