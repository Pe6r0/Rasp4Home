#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace rasp4home
{
namespace ui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void paletteSetup();
};
}
}
#endif // MAINWINDOW_H
