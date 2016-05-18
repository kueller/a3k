#include "a3kconsole.h"
#include "ui_a3kconsole.h"

a3kconsole::a3kconsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::a3kconsole)
{
    ui->setupUi(this);
    ui->console->setWordWrapMode(QTextOption::WrapAnywhere);
}

a3kconsole::~a3kconsole()
{
    delete ui;
}

// Console overwrites characters instead of inserting.
// Only prints text. Receiving text not yet implemented.
void a3kconsole::write_char(QString s, int addr)
{
    ui->console->setOverwriteMode(true);
    ui->console->moveCursor(QTextCursor::Start);
    for (int i = 4000 + 1; i <= addr; i++)
        ui->console->moveCursor(QTextCursor::NextCharacter);

    ui->console->textCursor().deleteChar();
    ui->console->textCursor().insertText(s);

    ui->console->setOverwriteMode(false);
}
