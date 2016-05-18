#include "a3kspeedselect.h"
#include "ui_a3kspeedselect.h"

#include "a3k.h"

a3kSpeedSelect::a3kSpeedSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::a3kSpeedSelect)
{
    ui->setupUi(this);
}

a3kSpeedSelect::~a3kSpeedSelect()
{
    delete ui;
}

void a3kSpeedSelect::on_pushButton_clicked()
{
    bool ok;
    int speed = ui->lineEdit->text().toInt(&ok);

    if (!ok) {
        ui->lineEdit->setText("");
    } else {
        if (speed >= MIN_SPEED && speed <= MAX_SPEED) {
            emit speedSelect(speed);
            this->hide();
        }
    }
}
