#include "draggablelabel.h"
#include <QApplication>

DraggableLabel::DraggableLabel(const QString &text, QWidget *parent) : QLabel(text, parent) {
    setAcceptDrops(true);
}
DraggableLabel::DraggableLabel(QWidget *parent) : QLabel(parent) {
    // Set default text if needed, or leave it empty.
    setAcceptDrops(true);
}

void DraggableLabel::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

void DraggableLabel::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(text());
    drag->setMimeData(mimeData);

    drag->exec(Qt::MoveAction);
}

void DraggableLabel::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void DraggableLabel::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasText()) {
        setText(event->mimeData()->text());
        event->acceptProposedAction();
    }
}
