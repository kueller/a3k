#ifndef A3KCONSOLE_H
#define A3KCONSOLE_H

#include <QDialog>

/*
 * The console for the virtual computer.
 * Prints values entered into video memory
 * starting at address 4000 (0x4a0).
 * User input is not yet implemented, only
 * properly prints. Text can still be
 * entered, but it won't do anything.
 */

namespace Ui {
class a3kconsole;
}

class a3kconsole : public QDialog
{
    Q_OBJECT

public:
    explicit a3kconsole(QWidget *parent = 0);
    ~a3kconsole();

public slots:
    void write_char(QString, int);

private:
    Ui::a3kconsole *ui;

};

#endif // A3KCONSOLE_H
