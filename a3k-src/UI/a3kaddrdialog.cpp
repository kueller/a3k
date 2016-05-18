#include "a3kaddrdialog.h"
#include "ui_a3kaddrdialog.h"

#include "a3k.h"

a3kaddrdialog::a3kaddrdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::a3kaddrdialog)
{
    ui->setupUi(this);
}

a3kaddrdialog::~a3kaddrdialog()
{
    delete ui;
}

// Make sure the address is within bounds, then send to
// "jump to address" in the main window.
void a3kaddrdialog::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    bool ok;
    int addr = text.toInt(&ok, 0);

    if (!ok) {
        ui->lineEdit->setText("");
    } else {
        if (addr >= 0 && addr < DEFAULT_MEM_SIZE + DEFAULT_VID_MEM_SIZE) {
            emit addrSearchSignal(addr);
            this->hide();
        } else {
            ui->lineEdit->setText("");
        }
    }
}
