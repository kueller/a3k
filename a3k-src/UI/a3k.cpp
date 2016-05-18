#include "a3k.h"
#include "ui_a3k.h"

#include "a3kconsole.h"
#include "a3kaddrdialog.h"
#include "a3kspeedselect.h"

// Register and memory arrays.
static uint32_t *regfile = NULL;
static uint32_t *memory = NULL;

// Dialog boxes from the options menu.
// Console displays values from the video memory.
static a3kconsole *console = NULL;
static a3kaddrdialog *jump = NULL;
static a3kSpeedSelect *speed = NULL;

// current_filename holds the name of the file (not the full path)
static bool file_loaded = false;
static QString current_filename = "";

// Timer which will determine the period of one "cycle".
static QTimer *timer = NULL;
static int timer_speed = 100;

static bool program_running = false;

a3k::a3k(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::a3k)
{
    ui->setupUi(this);

    regfile = initialize_regfile();
    memory = initialize_memory();

    populate_memory();
    populate_reg();

    console = new a3kconsole(this);
    jump = new a3kaddrdialog(this);
    speed = new a3kSpeedSelect(this);
    timer = new QTimer(this);

    connect(this, SIGNAL(vidMemoryUpdate(QString,int)), console, SLOT(write_char(QString, int)));
    connect(jump, SIGNAL(addrSearchSignal(int)), this, SLOT(jump_to_address(int)));
    connect(speed, SIGNAL(speedSelect(int)), this, SLOT(set_timer_speed(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(run_next()));
}

a3k::~a3k()
{
    free(regfile);
    free(memory);
    delete ui;
}

// Setup functions
void a3k::populate_memory()
{
    for (int i = 0; i < DEFAULT_MEM_SIZE + DEFAULT_VID_MEM_SIZE; i++) {
        ui->memList->addItem(QString("0x%1 | ").arg(i, 4, 16, QChar('0'))
                             + QString("0x%1").arg(memory[i], 8, 16, QChar('0')));
    }
}

void a3k::populate_reg()
{
    for (int i = 0; i < DEFAULT_REG_SIZE; i++) {
        ui->regList->addItem(QString("%1 | ").arg(i, 2, 10, QChar('0'))
                             + QString("0x%1").arg(regfile[i], 8, 16, QChar('0')));
    }
}

// Update a range of memory list blocks with the current value in memory
void a3k::update_memory(int start, int end)
{
    for (int i = start; i <= end; i++) {
        QListWidgetItem *slot = ui->memList->item(i);
        if (!slot) return;
        slot->setText(QString("%1 | ").arg(i, 4, 16, QChar('0'))
                     + QString("0x%1").arg(memory[i], 8, 16, QChar('0')));
    }
}

void a3k::update_reg(int row)
{
    QListWidgetItem *reg = ui->regList->item(row);
    if (!reg) return;
    reg->setText(QString("%1 | ").arg(row, 2, 10, QChar('0'))
                 + QString("0x%1").arg(regfile[row], 8, 16, QChar('0')));
}

void a3k::load_file()
{
    if (program_running) program_running = false;
    if (timer->isActive()) timer->stop();

    QString filename = QFileDialog::getOpenFileName(this, tr("Load Binary File"), ".");
    if (!filename.isNull()) {
         initialize_file(filename);
    }
}

// Loads the file into memory
void a3k::initialize_file(QString filename)
{
    QByteArray b = filename.toLatin1();
    const char *c_file = b.data();

    if (file_loaded) {
        reset_registers();
        reset_memory();
    }

    int e = load_program(memory, c_file);
    switch (e) {
    case A3K_IDLE:
    {
        update_memory(0, (int)current_mem_size() - 1);
        QStringList s = filename.split("/");
        QString base = s.at(s.size() - 1);
        ui->statusLabel->setText("File loaded: " + base);
        current_filename = base;
        reset_pc();
        file_loaded = true;
        jump_to_address(0);
        break;
    }
    case A3K_OVERFLOW:
        ui->statusLabel->setText("Error: OVERFLOW");
        break;
    case A3K_MEM_ERR:
        ui->statusLabel->setText("Error: MEMORY ERROR");
        break;
    case A3K_NULL_PTR:
        ui->statusLabel->setText("Error: NULL POINTER DEREFERENCE");
        break;
    case A3K_IO_ERR:
        ui->statusLabel->setText("Error: I/O ERROR");
        break;
    case A3K_OUT_OF_RANGE:
        ui->statusLabel->setText("Error: OUT OF RANGE");
        break;
    default:
        break;
    }

}

// Resets the values of the registers, not the list widget.
void a3k::reset_registers()
{
    for (int i = 0; i < DEFAULT_REG_SIZE; i++)
        regfile[i] = 0;
}

// Same as above but for memory.
void a3k::reset_memory()
{
    for (int i = 0; i < DEFAULT_MEM_SIZE + DEFAULT_VID_MEM_SIZE; i++)
        memory[i] = 0;
}

void a3k::reset_program()
{
    reset_pc();
    jump_to_address(0);
    reset_registers();
    for (int i = 0; i < DEFAULT_REG_SIZE; i++)
        update_reg(i);
}

// Called from the jump to address dialog.
void a3k::jump_to_address(int address)
{
    ui->memList->setCurrentRow(address);
}

// Called from the execution period dialog
void a3k::set_timer_speed(int new_speed)
{
    timer_speed = new_speed;
}

// Checks if there was a store (st or str), and returns the address changed.
// Bit twiddling to avoid updating all memory blocks every cycle.
int a3k::memory_changed(uint32_t insn)
{
    if ((insn & OP_MASK) == MEM && ((insn >> 5) & OP2_MASK) == OP2_2)
        return (insn >> 13);
    if ((insn & OP_MASK) == MEM) {
        if (((insn >> 5) & OP2_MASK) == OP2_2)
            return (insn >> 13);
        else if (((insn >> 5) & OP2_MASK) == OP2_4)
            return regfile[(insn >> 13) & REG_MASK];
    }

    return -1;
}

// Execute a single "cycle". Calls "execute_next".
bool a3k::run_next()
{
    if (!file_loaded)
        return false;

    int mem_update = memory_changed(memory[current_pc()]);

    int status = execute_next(memory, regfile);

    if (status == A3K_RUNNING) {

        jump_to_address(current_pc());

        for (int i = 0; i < DEFAULT_REG_SIZE; i++)
            update_reg(i);

        if (mem_update != -1)
            update_memory(mem_update, mem_update);
        if (mem_update >= DEFAULT_MEM_SIZE)
            emit vidMemoryUpdate(QString(char(memory[mem_update])), mem_update);
    } else {
        switch (status) {
        case A3K_MEM_ERR:
            ui->statusLabel->setText("Error: MEMORY ERROR");
            break;
        case A3K_OUT_OF_RANGE:
            ui->statusLabel->setText("Error: OUT OF RANGE");
            break;
        case A3K_IO_ERR:
            ui->statusLabel->setText("Error: I/O ERROR");
            break;
        case A3K_DIVIDE_BY_ZERO:
            ui->statusLabel->setText("Error: DIVIDE BY ZERO");
            break;
        case A3K_IDLE:
            ui->statusLabel->setText("File loaded: " + current_filename);
            break;
        }

        program_running = false;
        if (timer->isActive())
            timer->stop();
    }

    return status == A3K_RUNNING;
}

// Buttons and options

void a3k::on_actionLoad_File_triggered()
{
    load_file();
}

void a3k::on_actionJump_To_Address_triggered()
{
    jump->show();
}

void a3k::on_actionShow_Console_triggered()
{
    console->show();
}

void a3k::on_runButton_clicked()
{
    if (!program_running) {
        program_running = true;
        ui->statusLabel->setText("Program running.");
    }

    timer->start(timer_speed);
}

void a3k::on_runFastButton_clicked()
{
    if (!program_running) {
        program_running = true;
        ui->statusLabel->setText("Program running.");
    }

    while(run_next());
}

void a3k::on_stepButton_clicked()
{
    if (!program_running) {
        program_running = true;
        ui->statusLabel->setText("Step mode.");
    }
    run_next();
}

void a3k::on_pauseButton_clicked()
{
    if (program_running) {
        program_running = false;
        ui->statusLabel->setText("Paused.");
    }

    if (timer->isActive())
        timer->stop();
}

void a3k::on_stopButton_clicked()
{
    if (program_running) {
        program_running = false;
        ui->statusLabel->setText("File loaded: " + current_filename);
    }

    if (timer->isActive())
        timer->stop();
    reset_program();
}

void a3k::on_actionExit_triggered()
{
    this->close();
}

void a3k::on_actionSet_Speed_triggered()
{
    speed->show();
}
