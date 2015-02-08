#include "detailswindow.h"
#include "ui_detailswindow.h"

DetailsWindow::DetailsWindow(int current_season, QString team_number, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::DetailsWindow),
	season(current_season),
	number(team_number)
{
	ui->setupUi(this);

	QString title = "Herodotus - Team #" + number + ": ";
	this->setWindowTitle(title);

	ui->label_number->setText("Team #" + number);
}

DetailsWindow::~DetailsWindow()
{
	delete ui;
}

void DetailsWindow::on_pushButton_close_clicked()
{
	this->close();
	this->deleteLater();
}
