#ifndef A3K_H
#define A3K_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>
#include <cstdint>

#include "../a3ksetup.h"
#include "../execute.h"

// Periods of execution
#define MIN_SPEED 50
#define MAX_SPEED 300

/* I don't know C++ I'm sorry. */

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
    void on_actionLoad_File_triggered();

    void on_actionJump_To_Address_triggered();

    void on_actionShow_Console_triggered();

    bool run_next();

    void on_runButton_clicked();

    void on_runFastButton_clicked();

    void on_stepButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_actionExit_triggered();

    void on_actionSet_Speed_triggered();

public slots:
    void jump_to_address(int);
    void set_timer_speed(int);

private:
    Ui::a3k *ui;
    void populate_memory();
    void populate_reg();
    void update_memory(int, int);
    void update_reg(int);
    void load_file();
    void initialize_file(QString);
    void reset_registers();
    void reset_memory();
    void reset_program();
    int memory_changed(uint32_t);

signals:
    void vidMemoryUpdate(QString, int);
};

#endif // A3K_H
