#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>
#include <QVector>

namespace Ui {
class Diagram;
}

class Diagram final : public QWidget
{
    Q_OBJECT

    using Layer = QVector<double>;

public:
    explicit Diagram(QWidget *parent = 0);
    ~Diagram();

    void    showLayer(const Layer& layer, double h, int index);

signals:
    void    prevLayerRequest();
    void    nextLayerRequest();

private slots:
    void    on_prevButton_clicked();
    void    on_nextButton_clicked();

private:
    Ui::Diagram *ui;
};

#endif // DIAGRAM_H
