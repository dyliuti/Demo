#ifndef COMMANDS_H
#define COMMANDS_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QUndoCommand>

class AddCommand : public QUndoCommand {
public:
    AddCommand(QGraphicsItem* item, QGraphicsScene* scene);

    // QUndoCommand interface
    void undo() override;
    void redo() override;

private:
    QGraphicsItem* mItem;
    QGraphicsScene* mScene;
};

class RemoveCommand : public QUndoCommand {
public:
    RemoveCommand(QGraphicsItem* item, QGraphicsScene* scene);

    // QUndoCommand interface
    void undo() override;
    void redo() override;

private:
    QGraphicsItem* mItem;
    QGraphicsScene* mScene;
};

class MoveCommand : public QUndoCommand {
public:
    MoveCommand(QGraphicsItem* item, QGraphicsScene* scene,
        QPointF oldPos, QPointF newPos);

    // QUndoCommand interface
    void undo() override;
    void redo() override;

private:
    QGraphicsItem* mItem;
    QGraphicsScene* mScene;
    QPointF mOldPosition;
    QPointF mNewPosition;
};

#endif // COMMANDS_H
