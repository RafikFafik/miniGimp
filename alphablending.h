#ifndef ALPHABLENDING_H
#define ALPHABLENDING_H

#include <QWidget>

namespace Ui {
class AlphaBlending;
}

class AlphaBlending : public QWidget
{
    Q_OBJECT

public:
    explicit AlphaBlending(QWidget *parent = nullptr);
    ~AlphaBlending();

private:
    Ui::AlphaBlending *ui;
};

#endif // ALPHABLENDING_H
