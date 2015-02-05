#include "dispwindow.h"
#include "ui_dispwindow.h"

DispWindow::DispWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DispWindow),
{
	ui->setupUi(this);
}

DispWindow::~DispWindow()
{
	delete ui;
}

