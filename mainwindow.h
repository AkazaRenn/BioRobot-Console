#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GAMEPAD_POLLING_INTERVAL 200
#define GAMEPAD_TCP_PORT 51234
#define TRAJ_TCP_PORT 51235

#include "video/fullscreenwindow.h"
#include "gamepad/gamepadreader.h"
#include "trajectory/trajectoryreceiver.h"

#include <QMainWindow>
#include <QQuickWidget>
#include <QWebEngineView>
#include <QWebEngineFullScreenRequest>
#include <QGamepad>
#include <QTcpSocket>

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
    GamepadReader* gamepadReader;
    QTcpSocket* gamepadSocket;
    QTcpSocket* trajectorySocket;
    TrajectoryReceiver* trajectoryReceiver;
    QObject* trajectoryDataModel;

private slots:
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    void onConnectButtonClicked();
};
#endif // MAINWINDOW_H
