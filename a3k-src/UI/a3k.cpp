#include "a3k.h"
#include "ui_a3k.h"

static uint16_t *isr = NULL;
static int *reg = NULL;

static QTimer *timer = NULL;
static int timer_speed = 100;

static bool file_loaded = false;

a3k::a3k(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::a3k)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run_next()));

    ui->action100_2->setChecked(true);
}

a3k::~a3k()
{
    if (file_loaded) {
        free(isr);
        free(reg);
    }

    delete ui;
}

void a3k::initialize(QString filename)
{
    QByteArray b = filename.toLatin1();
    const char *c_file = b.data();

    isr = initialize_instruction_reg(c_file);
    populate_lists();

    highlight_current();

    reg = initialize_regfile();
    update_registers();
    file_loaded = true;
}

void a3k::load_file()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load Binary File"), ".");
    if (!filename.isNull()) {
        if (file_loaded)
            reset_everything();

        QStringList s = filename.split("/");
        QString base = s.at(s.size() - 1);
        ui->fileLabel->setText("File Loaded: " + base);

        initialize(filename);
    }
}

void a3k::reset_program()
{
    reset_pc();
    highlight_current();
    for (int i = 0; i < 8; i++)
        reg[i] = 0;
    update_registers();
}

void a3k::reset_everything()
{
    if (!file_loaded) return;

    ui->addrList->clear();
    ui->insnList->clear();
    ui->opList->clear();
    for (int i = 0; i < 8; i++)
        reg[i] = 0;
    update_registers();
    free(isr);
    free(reg);
    file_loaded = false;
}

void a3k::highlight_current()
{
    ui->addrList->setCurrentRow(current_pc());
    ui->insnList->setCurrentRow(current_pc());
    ui->opList->setCurrentRow(current_pc());
}

void a3k::populate_lists()
{
    if (isr) {
        for (int i = 0; isr[i]; i++) {
            ui->insnList->addItem(QString("0x%1").arg(isr[i], 4, 16, QChar('0')));
            ui->addrList->addItem(QString("0x%1").arg(i, 4, 16, QChar('0')));
            ui->opList->addItem(generate_op(isr[i]));
        }
    } else {
        ui->fileLabel->setText("Error loading file");
    }
}

void a3k::update_registers()
{
    ui->reg_0->setText(QString::number(reg[0]));
    ui->reg_1->setText(QString::number(reg[1]));
    ui->reg_2->setText(QString::number(reg[2]));
    ui->reg_3->setText(QString::number(reg[3]));
    ui->reg_4->setText(QString::number(reg[4]));
    ui->reg_5->setText(QString::number(reg[5]));
    ui->reg_6->setText(QString::number(reg[6]));
    ui->reg_7->setText(QString::number(reg[7]));
    ui->reg_8->setText(QString::number(reg[8]));
}

bool a3k::run_next()
{
    int status = execute_next(isr, reg);
    if (status) {
        highlight_current();
        update_registers();
    } else {
        if (timer->isActive())
            timer->stop();
    }
    return status;
}

void a3k::on_runButton_clicked()
{
    timer->start(timer_speed);
}

void a3k::on_fastButton_clicked()
{
    while (run_next());
}

void a3k::on_stepButton_clicked()
{
    run_next();
}

void a3k::on_Pause_clicked()
{
    if (timer->isActive())
        timer->stop();
}

void a3k::on_stopButton_clicked()
{
    if (timer->isActive())
        timer->stop();
    reset_program();
}

void a3k::on_actionOpen_triggered()
{
    load_file();
}

void a3k::on_action50_triggered()
{
    if (ui->action100_2->isChecked()) ui->action100_2->setChecked(false);
    if (ui->action200_2->isChecked()) ui->action200_2->setChecked(false);
    if (ui->action300_2->isChecked()) ui->action300_2->setChecked(false);
    timer_speed = 50;
}

void a3k::on_action100_2_triggered()
{
    if (ui->action50->isChecked()) ui->action50->setChecked(false);
    if (ui->action200_2->isChecked()) ui->action200_2->setChecked(false);
    if (ui->action300_2->isChecked()) ui->action300_2->setChecked(false);
    timer_speed = 100;
}

void a3k::on_action200_2_triggered()
{
    if (ui->action50->isChecked()) ui->action50->setChecked(false);
    if (ui->action100_2->isChecked()) ui->action100_2->setChecked(false);
    if (ui->action300_2->isChecked()) ui->action300_2->setChecked(false);
    timer_speed = 200;
}

void a3k::on_action300_2_triggered()
{
    if (ui->action50->isChecked()) ui->action50->setChecked(false);
    if (ui->action100_2->isChecked()) ui->action100_2->setChecked(false);
    if (ui->action200_2->isChecked()) ui->action200_2->setChecked(false);
    timer_speed = 300;
}
