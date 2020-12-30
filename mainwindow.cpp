#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickItem>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineFullScreenRequest>
#include <QTimer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QRegExpValidator>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_view(new QWebEngineView(this))
{
    ui->setupUi(this);

    ((QVBoxLayout *)ui->centralwidget->layout())->insertWidget(0, m_view);
    m_view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    QSizePolicy m_view_size_policy = m_view->sizePolicy();
    m_view_size_policy.setHorizontalPolicy(QSizePolicy::Expanding);
    m_view->setSizePolicy(m_view_size_policy);
    connect(m_view->page(),
            &QWebEnginePage::fullScreenRequested,
            this,
            &MainWindow::fullScreenRequested);
    m_view->load(QUrl(QStringLiteral("qrc:/index.html")));

    gamepadSocket = new QTcpSocket(this);
    gamepad = ui->gamepadWidget->rootObject()->findChild<QGamepad *>("gamepad");
    gamepadPollingTimer = new QTimer(this);
    gamepadPollingTimer->setSingleShot(true);
    gamepadPollingTimer->setInterval(GAMEPAD_POLLING_INTERVAL);
    gamepadPollingTimer->setTimerType(Qt::PreciseTimer);
    gamepadReader = new GamepadReader(this);
    connect(gamepadPollingTimer, &QTimer::timeout, gamepadReader, QOverload<>::of(&GamepadReader::readGamepad));

    // set robot address to only allow IPv4 and IPv6 formats
    ui->robotAddressEdit->setValidator(new QRegExpValidator(QRegExp(
        "((^\\s*((([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))\\s*$)|(^\\s*((([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4}|:))|(([0-9A-Fa-f]{1,4}:){6}(:[0-9A-Fa-f]{1,4}|((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){5}(((:[0-9A-Fa-f]{1,4}){1,2})|:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){4}(((:[0-9A-Fa-f]{1,4}){1,3})|((:[0-9A-Fa-f]{1,4})?:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){3}(((:[0-9A-Fa-f]{1,4}){1,4})|((:[0-9A-Fa-f]{1,4}){0,2}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){2}(((:[0-9A-Fa-f]{1,4}){1,5})|((:[0-9A-Fa-f]{1,4}){0,3}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){1}(((:[0-9A-Fa-f]{1,4}){1,6})|((:[0-9A-Fa-f]{1,4}){0,4}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(:(((:[0-9A-Fa-f]{1,4}){1,7})|((:[0-9A-Fa-f]{1,4}){0,5}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:)))(%.+)?\\s*$))")));

    connect(ui->connectButton, &QPushButton::released, this, &MainWindow::onConnectButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fullScreenRequested(QWebEngineFullScreenRequest request)
{
    if (request.toggleOn())
    {
        if (m_fullScreenWindow)
            return;
        request.accept();
        m_fullScreenWindow.reset(new FullScreenWindow(m_view));
    }
    else
    {
        if (!m_fullScreenWindow)
            return;
        request.accept();
        m_fullScreenWindow.reset();
    }
}

void MainWindow::onConnectButtonClicked()
{
    gamepadSocket->connectToHost(QHostAddress(ui->robotAddressEdit->text()), GAMEPAD_TCP_PORT);
    if (!gamepadSocket->isValid())
    {
        ui->robotAddressEdit->setText("INVALID ADDRESS");
    }

    gamepadReader->setGamepad(gamepad);
    gamepadPollingTimer->start();
}
