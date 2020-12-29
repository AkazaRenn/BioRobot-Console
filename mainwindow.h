#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "video/fullscreenwindow.h"

#include <QMainWindow>
#include <QQuickWidget>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>
#include <QGamepad>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWebEngineView *m_view;
    QScopedPointer<FullScreenWindow> m_fullScreenWindow;
    QGamepad *gamepad;
    QTimer *gamepadPollingTimer;
    void pollGamepadInput();

private slots:
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    void on_connectButton_clicked();
};
#endif // MAINWINDOW_H
