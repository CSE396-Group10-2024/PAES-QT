// DraggableLabel.h

#ifndef DRAGGABLELABEL_H
#define DRAGGABLELABEL_H

#include <QLabel>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>

class DraggableLabel : public QLabel {
    Q_OBJECT
public:
    explicit DraggableLabel(const QString &text, QWidget *parent = nullptr);
    explicit DraggableLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    QPoint dragStartPosition;
};

#endif // DRAGGABLELABEL_H
