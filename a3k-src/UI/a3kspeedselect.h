#ifndef A3KSPEEDSELECT_H
#define A3KSPEEDSELECT_H

#include <QDialog>

/*
 * Speed was a bad choice of word. This
 * determines the period (higher value
 * means slower execution).
 */

namespace Ui {
class a3kSpeedSelect;
}

class a3kSpeedSelect : public QDialog
{
    Q_OBJECT

public:
    explicit a3kSpeedSelect(QWidget *parent = 0);
    ~a3kSpeedSelect();

private slots:
    void on_pushButton_clicked();

private:
    Ui::a3kSpeedSelect *ui;

signals:
    void speedSelect(int);
};

#endif // A3KSPEEDSELECT_H
