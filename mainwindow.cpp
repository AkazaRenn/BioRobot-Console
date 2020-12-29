#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickItem>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineFullScreenRequest>
#include <QTimer>

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

    gamepad = ui->gamepadWidget->rootObject()->findChild<QGamepad *>("gamepad");
    gamepadPollingTimer = new QTimer(this);
    gamepadPollingTimer->setSingleShot(false);
    gamepadPollingTimer->setInterval(200);
    connect(gamepadPollingTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::pollGamepadInput));
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

void MainWindow::pollGamepadInput()
{
    printf("Timer times out!");
}

void MainWindow::on_connectButton_clicked()
{
    printf("Connect button clicked!");
    gamepadPollingTimer->start();
}
