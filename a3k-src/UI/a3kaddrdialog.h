#ifndef A3KADDRDIALOG_H
#define A3KADDRDIALOG_H

#include <QDialog>

/* Box to get a user input address to jump to directly
 * to avoid scrolling. Accepts octal, hex, and decimal
 * representations.
 */

namespace Ui {
class a3kaddrdialog;
}

class a3kaddrdialog : public QDialog
{
    Q_OBJECT

public:
    explicit a3kaddrdialog(QWidget *parent = 0);
    ~a3kaddrdialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::a3kaddrdialog *ui;

signals:
    void addrSearchSignal(int addr);
};

#endif // A3KADDRDIALOG_H
