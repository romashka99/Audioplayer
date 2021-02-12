#pragma
#ifndef FILE_H
#define FILE_H
#include "product.h"
#include <QDateTime>

class File : public Product
{
private:
    QString path;
    QDateTime dateAdded;
    QString language;
public:
    File(QString const& name, QString const& path, QDateTime const& date, QString const& language);
    void setPath(QString const& path);
    QString getPath();
    void setDateAdded(QDateTime const& date);
    QDateTime getDateAdded();
    void setLanguage(QString const& language);
    QString getLanguage();
};

#endif // FILE_H
