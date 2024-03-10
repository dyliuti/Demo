#ifndef WEB_VIEW_BASE_H
#define WEB_VIEW_BASE_H

#include <QObject>
#include "widget_global.h"
#include <QWidget>

class WIDGET_EXPORT WebViewBase : public QWidget
{
    Q_OBJECT
public:
    using QWidget::QWidget;


signals:
    void signalPageLoadFinished();
};

#endif // WEB_VIEW_BASE_H
