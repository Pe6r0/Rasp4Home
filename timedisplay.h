#ifndef TIMEDISPLAY_H
#define TIMEDISPLAY_H

#include <QWidget>
#include <QLabel>

namespace rasp4home
{
namespace ui
{
class TimeDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit TimeDisplay(QWidget *parent = nullptr);
    QLabel mHours{"00", this};
    QLabel mMinutes{"00", this};
    QLabel mSeconds{"00", this};
    QLabel mSeparator{":", this};

signals:

};
}
}

#endif // TIMEDISPLAY_H
