#ifndef DOUBLECLICKBUTTON_H
#define DOUBLECLICKBUTTON_H

#include <QPushButton>

class DoubleclickButton : public QPushButton {
    Q_OBJECT
public:
    explicit DoubleclickButton(QWidget* parent = nullptr);

signals:
    void doubleClicked();

protected:
    void mouseDoubleClickEvent(QMouseEvent* event) override;
};

#endif // DOUBLECLICKBUTTON_H
