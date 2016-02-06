#ifndef A3K_H
#define A3K_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>
#include <QFileDialog>
#include <cstdint>

#include "instructionops.h"
#include "../a3ksetup.h"
#include "../execute.h"

namespace Ui {
class a3k;
}

class a3k : public QMainWindow
{
    Q_OBJECT

public:
    explicit a3k(QWidget *parent = 0);
    ~a3k();

private slots:
    void initialize(QString filename);
    void load_file();
    void reset_program();
    void reset_everything();
    void populate_lists();
    void highlight_current();
    void update_registers();
    bool run_next();

    void on_runButton_clicked();

    void on_fastButton_clicked();

    void on_stepButton_clicked();

    void on_Pause_clicked();

    void on_stopButton_clicked();

    void on_actionOpen_triggered();

    void on_action50_triggered();

    void on_action100_2_triggered();

    void on_action200_2_triggered();

    void on_action300_2_triggered();


private:
    Ui::a3k *ui;
};

#endif // A3K_H
