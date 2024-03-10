#ifndef WEB_WIDGET_BASE_H
#define WEB_WIDGET_BASE_H

#include <QObject>
#include <QWidget>
#include <QFrame>
#include "widget_global.h"
#include "webbridgebase.h"
#include "webviewbase.h"

/*** 无边框前端页面基类，可设置阴影，关闭按钮，圆角大小
 * 重写接口createWebBridge()针对与不同前端交互业务逻辑.
 * 继承 WebBridge and WebWidgetBase ***/
class QPushButton;
//widget which shows web, contains webview and bridge
class WIDGET_EXPORT WebWidgetBase : public QFrame
{
    Q_OBJECT
public:
    using QFrame::QFrame;
    virtual void init(const QString &webUrl = "www.baidu.com", const QString &bridgeName = "");
    void setCloseButtonEnable(bool enbale) { m_closeButtonEnable = enbale; }
    void setWebCornerRadius(int value) { m_webCornerRadius = value; }
    template<class T>
    std::shared_ptr<T> getTypicalBridge()
    {
        return std::dynamic_pointer_cast<T>(m_bridge);
    };

signals:
    void sigPageLoadFinish();
    void sigClose();

protected:
    virtual std::shared_ptr<WebBridgeBase> createWebBridge();
    void createCloseButton();

protected:
    void resizeEvent(QResizeEvent *event) override;

protected:
    WebViewBase *m_webView = nullptr;
    std::shared_ptr<WebBridgeBase> m_bridge;
    bool m_closeButtonEnable = false;
    bool m_bLoadFinish = false;
    int m_webCornerRadius = 0;

private:
    QPushButton *m_closeButton = nullptr;
};

// container which contasin title bar(if need)、web、bottom (if need)
class WIDGET_EXPORT WebWindowBase : public QFrame
{
    Q_OBJECT
public:
    static const QMargins SHADOW_MARGINS;
    using QFrame::QFrame;
    virtual void init();
    virtual void show();
    void setWebWidgetSize(int width, int height);
    void moveToCenter(QWidget *parent = nullptr);
    void setRadius(int radius) { m_radius = radius; }
    void setShadowEanbel(bool enable) { m_shadowEnable = enable; }
    template<class T>
    std::shared_ptr<T> getTypicalBridge()
    {
        return m_webWidget ? m_webWidget->getTypicalBridge<T>() : nullptr;
    };

signals:
    void sigClose();

protected:
    virtual QWidget *createTitleBar();
    virtual QWidget *createBottomBar();
    virtual WebWidgetBase *createWebWidget();
    virtual void initWindowFlags();
    void createShadow();

protected:
    void closeEvent(QCloseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

protected:
    WebWidgetBase *m_webWidget = nullptr;
    QWidget *m_titleWidget = nullptr;
    QWidget *m_bottomWidget = nullptr;
    int m_radius = 8;
    bool m_shadowEnable = true;
};

// model container which contasin title bar(if need)、web、bottom (if need)
class WIDGET_EXPORT WebDialogBase : public WebWindowBase
{
    Q_OBJECT
public:
    using WebWindowBase::WebWindowBase;
    virtual int exec();

protected:
    void initWindowFlags() override;
};

#endif // WEB_WIDGET_BASE_H
