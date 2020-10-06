#ifndef TRANSFORMATION2D_H
#define TRANSFORMATION2D_H

#include <QWidget>

namespace Ui {
class Transformation2D;
}

class Transformation2D : public QWidget
{
    Q_OBJECT

public:
    explicit Transformation2D(QWidget *parent = nullptr);
    ~Transformation2D();

private:
    Ui::Transformation2D *ui;
};

#endif // TRANSFORMATION2D_H
