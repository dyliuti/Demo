#include "webwidgetbase.h"
#include <QUrl>
#include <QVBoxLayout>
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QTimer>
#include <QDebug>

const QMargins WebWindowBase::SHADOW_MARGINS = QMargins(50, 50, 50, 50);

void WebWidgetBase::init(const QString &webUrl, const QString &bridgeName)
{
    setAttribute(Qt::WA_TranslucentBackground);
    m_webView = new WebViewBase(this);

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget((QWidget *) m_webView);
    setLayout(vLayout);

    createCloseButton();
    m_bridge = createWebBridge();
//    m_webView->registerObject(m_bridge.get(), bridgeName);
    connect(m_bridge.get(), &WebBridgeBase::sigClose, this, &WebWidgetBase::sigClose);

    connect(m_webView, &WebViewBase::signalPageLoadFinished, this, &WebWidgetBase::sigPageLoadFinish);
    connect(m_webView, &WebViewBase::signalPageLoadFinished, this, [&] {
        m_bLoadFinish = true;
    });
//    m_webView->webPage()->load(QUrl(webUrl), "");
//    m_webView->setCefCornerRadius(m_webCornerRadius);
}

std::shared_ptr<WebBridgeBase> WebWidgetBase::createWebBridge()
{
    return std::make_shared<WebBridgeBase>(m_webView);
}

void WebWidgetBase::createCloseButton()
{
    if (m_closeButtonEnable) {
        m_closeButton = new QPushButton(this);
        m_closeButton->setObjectName("btn_close");
        m_closeButton->setFixedSize(30, 24);
        m_closeButton->setStyleSheet("QPushButton#btn_close{ background: transparent; border: none;image: url(:/im/images/MainWindow/close_normal.svg); }"
                                     "QPushButton#btn_close:hover { image: url(:/im/images/MainWindow/close_hover.svg); }"
                                     "QPushButton#btn_close:pressed { image: url(:/im/images/MainWindow/close_pressed.svg); }");
        connect(m_closeButton, &QPushButton::clicked, this, &WebWidgetBase::sigClose);
        // if after 1s, load page finish
        connect(m_webView, &WebViewBase::signalPageLoadFinished, this, [=] {
            m_closeButton->setVisible(false);
        });
        m_closeButton->setVisible(false);
        QTimer::singleShot(1000, this, [=] {
            if (m_bLoadFinish) {
                return;
            }
            emit sigPageLoadFinish(); // show web widget, web window
            m_closeButton->setVisible(true);
        });
    }
}

void WebWidgetBase::resizeEvent(QResizeEvent *event)
{
    if (m_closeButton) {
        m_closeButton->setGeometry(width() - m_closeButton->width() - 11, 12, 30, 24);
        if (!m_closeButton->isHidden()) {
            m_closeButton->raise();
        }
    }

    QFrame::resizeEvent(event);
}

void WebWindowBase::init()
{
    setAttribute(Qt::WA_TranslucentBackground);

    createShadow();
    m_titleWidget = createTitleBar();
    m_bottomWidget = createBottomBar();
    m_webWidget = createWebWidget();
    m_webWidget->hide();
    connect(m_webWidget, &WebWidgetBase::sigPageLoadFinish, m_webWidget, &WebWidgetBase::show);
    connect(m_webWidget, &WebWidgetBase::sigPageLoadFinish, this, &WebWindowBase::show);
    initWindowFlags();

    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);

    if (!m_titleWidget) {
        vLayout->addWidget(m_titleWidget);
    }
    vLayout->addWidget(m_webWidget);
    vLayout->setAlignment(m_webWidget, Qt::AlignCenter);
    if (!m_bottomWidget) {
        vLayout->addWidget(m_bottomWidget);
    }
    setLayout(vLayout);
}

void WebWindowBase::show()
{
    QFrame::show();
    QApplication::setActiveWindow(this);
}

void WebWindowBase::setWebWidgetSize(int width, int height)
{
    if (m_webWidget == nullptr) {
        return;
    }

    if (m_shadowEnable) {
        setFixedSize(width + SHADOW_MARGINS.left() + SHADOW_MARGINS.right(),
                     height + SHADOW_MARGINS.top() + SHADOW_MARGINS.bottom() + (m_titleWidget ? m_titleWidget->height() : 0) + (m_bottomWidget ? m_bottomWidget->height() : 0));
    } else {
        setFixedSize(width,
                     height + (m_titleWidget ? m_titleWidget->height() : 0) + (m_bottomWidget ? m_bottomWidget->height() : 0));
    }
    m_webWidget->setFixedSize(width, height);
}

void WebWindowBase::moveToCenter(QWidget *parent)
{
    if (!parent) {
        return;
    }

    auto globalPos = parent->mapToGlobal(parent->pos());
    move(globalPos.x() + (parent->width() - width()) / 2,
         globalPos.y() + (parent->height() - height()) / 2);
}

QWidget *WebWindowBase::createTitleBar()
{
    return nullptr;
}

QWidget *WebWindowBase::createBottomBar()
{
    return nullptr;
}

WebWidgetBase *WebWindowBase::createWebWidget()
{
    return new WebWidgetBase(this);
}

void WebWindowBase::initWindowFlags()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Tool);
}

void WebWindowBase::createShadow()
{
    if (m_shadowEnable) {
        auto shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setOffset(0, 0);
        shadowEffect->setColor(QColor(0, 0, 0, 50));
        shadowEffect->setBlurRadius(50);
        setGraphicsEffect(shadowEffect);
    }
}

void WebWindowBase::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    emit sigClose();
}

#include <QPainterPath>
#include <QPen>
#include <QPainter>
#include <QDebug>
void WebWindowBase::paintEvent(QPaintEvent *event)
{
    QRect r = rect().adjusted(SHADOW_MARGINS.left() - m_radius, SHADOW_MARGINS.top() - m_radius, -SHADOW_MARGINS.right() + m_radius, -SHADOW_MARGINS.bottom() + m_radius);
    QPainterPath path;
    path.addRoundedRect(r, m_radius, m_radius);

    //    QPen pen(QColor("#2D2F30"));
    //    pen.setWidth(2);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    //    p.setPen(pen);
    p.setPen(Qt::NoPen);
    p.fillPath(path, QBrush(QColor(255, 255, 255)));
    p.drawPath(path);

    QWidget::paintEvent(event);
}

#include <QEventLoop>
int WebDialogBase::exec()
{
    QEventLoop loop;
    showNormal();
    hide();
    connect(this, &WebDialogBase::sigClose, &loop, &QEventLoop::quit);
    loop.exec(QEventLoop::DialogExec);
    return 0;
}

void WebDialogBase::initWindowFlags()
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);
}
