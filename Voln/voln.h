#ifndef VOLN_H
#define VOLN_H

#include <QWidget>

namespace Ui {
class Voln;
}

class Voln : public QWidget
{
    Q_OBJECT

public:
    explicit Voln(QWidget *parent = 0);
    ~Voln();

private:
    Ui::Voln *ui;
};

#endif // VOLN_H
