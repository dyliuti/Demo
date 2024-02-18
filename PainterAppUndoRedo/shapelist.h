#ifndef SHAPELIST_H
#define SHAPELIST_H

#include <QListWidget>

class ShapeList : public QListWidget {
    Q_OBJECT
public:
    explicit ShapeList(QWidget* parent = nullptr);

protected:
    void startDrag(Qt::DropActions supportedActions) override;
};

#endif // SHAPELIST_H
