#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>

namespace rasp4home
{
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

signals:

};
}
#endif // DATAMANAGER_H
