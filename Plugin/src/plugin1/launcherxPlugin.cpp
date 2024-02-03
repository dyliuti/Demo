#include "LauncherxPlugin.h"

#include "extensionsystem/pluginmanager.h"
#include <QtPlugin>
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QMovie>
#include "extension.h"
#include "network/EeoNetworkUtil.h"
#include "CoreEngine/CoreEngine.h"
#include "network/EeoNetworkConfig.h"
#include "CoreEngine/loginobject.h"
#include "PluginObjectInterface/ILoginMgr.h"

NAMESPACE_LAUNCHERX_USE
LauncherxPlugin::LauncherxPlugin()
{
}

LauncherxPlugin::~LauncherxPlugin()
{
}

bool LauncherxPlugin::load()
{
    EeoNetworkConfig::setIsLoginFunc([=]() {
        return EeoEngine::CoreEngine::instance()->loginObject()->isLogined();
    });
    EeoNetworkConfig::setGetAppSecretFunc([=]() {
        return EeoEngine::CoreEngine::instance()->getAppSecret();
    });
    EeoNetworkConfig::setGetCurrentTimeFunc([=]() {
        return EeoEngine::CoreEngine::instance()->getCurTime();
    });
    EeoNetworkConfig::setGetCurrentUidFunc([=]() {
        return EeoEngine::CoreEngine::instance()->getUid();
    });

    m_timer.start();
    auto screen = QGuiApplication::screenAt(QCursor::pos());
    const auto &screenRect = screen->geometry();
    m_launcherXWidget = new LauncherxWidget;
    m_launcherXWidget->setScreenInfo(QGuiApplication::screens().indexOf(screen), screen->size(), screen->devicePixelRatio());
    m_launcherXWidget->getConfig()->initLauncherScale(screenRect);
    m_launcherXWidget->init("qrc:/qml/launchx/Launchx3.qml");
    m_launcherXWidget->setGeometry(screenRect.x(), screenRect.y(), screenRect.width() + 1, screenRect.height());
    m_launcherXWidget->hide();

    m_pMgr = std::make_shared<LauncherxMgr>(m_launcherXWidget);
    Extension::instance()->addObject(m_pMgr.get());

    startupAnimation();

    return true;
}

void LauncherxPlugin::startupAnimation()
{
    QLabel *startLabel = new QLabel();
    startLabel->setAttribute(Qt::WA_TranslucentBackground);
    startLabel->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CoverWindow);
    startLabel->setFixedSize(600, 338);
    auto screen = QGuiApplication::screenAt(QCursor::pos());
    if (!screen)
        screen = qApp->primaryScreen();
    auto screenRect = screen->geometry();
    startLabel->move(screenRect.x() + (screenRect.width() - startLabel->width()) / 2,
                     screenRect.y() + (screenRect.height() - startLabel->height()) / 2);
    startLabel->setWindowFlags(startLabel->windowFlags() | Qt::FramelessWindowHint
                               | Qt::WindowStaysOnTopHint);
    QPixmap pixmap(":/images/start/start_classinX.png");
    auto pix = pixmap.scaled(startLabel->size() * startLabel->devicePixelRatioF(),
                             Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    pix.setDevicePixelRatio(startLabel->devicePixelRatioF());

    if (!EeoUtils::hasRegistedInstallInfo()) {
        BindInstallPlaceWidget *guideWidget = new BindInstallPlaceWidget(
            BindInstallPlaceWidget::InitType::Init);
        guideWidget->exec();
    }

    startLabel->setPixmap(pix);
    auto startMovie = new QMovie(this);
    startMovie->setFileName(":/images/start/start_classinX.gif");
    startMovie->start();
    connect(startMovie, &QMovie::frameChanged, this, [startMovie, startLabel]() {
        auto pixmap = startMovie->currentPixmap();
        auto pix = pixmap.scaled(startLabel->size() * startLabel->devicePixelRatioF(),
                                 Qt::KeepAspectRatio,
                                 Qt::SmoothTransformation);
        pix.setDevicePixelRatio(startLabel->devicePixelRatioF());
        startLabel->setPixmap(pix);
        startLabel->show();
    });
    connect(startMovie, &QMovie::finished, this, [this, startLabel, startMovie]() {
        startLabel->hide();
        startLabel->deleteLater();
        startMovie->deleteLater();
        if (m_pMgr) {
            m_pMgr->showLauncherxWidget();
        }
        LauncherxUtil::enterTheMainInterface(m_timer.elapsed() / 1000);

        if (m_launcherXWidget) {
            m_launcherXWidget->getLoginControl()->getLoginDialog();
        }
    });
}
