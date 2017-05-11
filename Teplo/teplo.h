#ifndef TEPLO_H
#define TEPLO_H

#include <QWidget>

namespace Ui {
class Teplo;
}

class Teplo : public QWidget
{
    Q_OBJECT

public:
    explicit Teplo(QWidget *parent = 0);
    ~Teplo();

private:
    Ui::Teplo *ui;
};

#endif // TEPLO_H
