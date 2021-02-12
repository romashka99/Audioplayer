#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include <QTextStream>
#include "music.h"
#include "audiobook.h"
#include <QFileInfo>

class DataBase
{
private:
    QList<Audio*>* listAudio;
    QString pathFromFile;
public:
    DataBase(QString const& path);
    ~DataBase();
    bool findAudio(Audio * audio);
    void updateDataBaseFromFile();
    int addAudio(Audio * audio);
    void deleteAudio(Audio * audio);
    QList<Audio*>* getListAudio();
    void setDataBaseFromFile();
    void editAudio(Audio * audio, Audio * editAudio);
    QList<Audio*>* searchString(QString inputData);
    void sort(int index, int status);
    QString getInformation();
    void setPathFromFile(QString const& path);
    QString getPathFromFile();
    void setStatusSort(int k);
};

#endif // DATABASE_H
