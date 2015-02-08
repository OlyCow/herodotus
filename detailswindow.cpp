#include "detailswindow.h"
#include "ui_detailswindow.h"

DetailsWindow::DetailsWindow(int current_season, QString team_number, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::DetailsWindow),
	timer_anim(new QTimer()),
	season(current_season),
	number(team_number)
{
	ui->setupUi(this);

	QString title = "Herodotus - Team #" + number + ": ";
	this->setWindowTitle(title);

	ui->label_number->setText("Team #" + number);

	QObject::connect(	timer_anim,	&QTimer::timeout,
						this,		&DetailsWindow::fwd_pic);
	timer_anim->setInterval(5000);
	timer_anim->start();
}

DetailsWindow::~DetailsWindow()
{
	delete timer_anim;
	delete ui;
}

void DetailsWindow::fwd_pic()
{
	;
}
void DetailsWindow::rev_pic()
{
	;
}

void DetailsWindow::on_pushButton_L_clicked()
{
	rev_pic();
}
void DetailsWindow::on_pushButton_R_clicked()
{
	fwd_pic();
}

void DetailsWindow::on_pushButton_close_clicked()
{
	this->close();
	this->deleteLater();
}
