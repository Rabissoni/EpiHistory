#include <QtGui>
#include <QKeyEvent>

class MyWidget : public QWidget
{
public:
    MyWidget();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent ( QKeyEvent * event );
};

MyWidget::MyWidget()
{
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
            QMessageBox::warning(this, "titre message box", "touche Left");
              break;
    case Qt::Key_Up:
            QMessageBox::warning(this, "titre message box", "touche Up");
              break;
    case Qt::Key_Right:
            QMessageBox::warning(this, "titre message box", "touche Right");
              break;
    case Qt::Key_Down:
            QMessageBox::warning(this, "titre message box", "touche Down");
    break;
    case Qt::Key_Escape:
            QMessageBox::warning(this, "titre message box", "touche Echap");
    break;
    }
    QWidget::keyPressEvent(event);
}


void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(Qt::darkBlue);

    QRectF Cadre(4, 4, 500, 590);

    QRectF Snake(50, 50, 10, 10);
    QRectF Apple(10, 10, 10, 10);

    painter.drawRect(Cadre);
    painter.setPen(Qt::darkGreen);
    painter.drawRect(Snake);

    painter.setBrush(QColor(255,0, 0, 255));
    painter.setPen(Qt::darkRed);
    painter.drawRoundRect(Apple);
    painter.drawRect(Apple);

    painter.setPen(Qt::darkGreen);
    painter.drawText(520, 52, "Highscore: ");
    painter.drawText(520, 80, "Score: ");
    painter.drawText(520, 95, "Apple: ");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyWidget widget;

    widget.setFixedSize(800, 600);
    widget.show();
    return app.exec();
}
