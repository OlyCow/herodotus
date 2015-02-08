#include "detailswindow.h"
#include "ui_detailswindow.h"

DetailsWindow::DetailsWindow(int current_season, QString team_number, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::DetailsWindow),
	timer_anim(new QTimer()),
	current_pic(new QPixmap()),
	season(current_season),
	number(team_number)
{
	ui->setupUi(this);

	QDir data_dir(QCoreApplication::applicationDirPath() + "/data/");
	QFile data_file(QString(data_dir.absolutePath() + Herodotus::name_text[season]));
	data_file.open(QFile::ReadOnly | QFile::Text);
	QTextStream buf(&data_file);
	QString data_read = buf.readLine();
	while (!buf.atEnd()) {
		data_read = buf.readLine();
		QRegularExpression finder("\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\"");
		QString number_temp = finder.match(data_read).captured(1);
		if (number_temp == number) {
			name = finder.match(data_read).captured(2);
			website = finder.match(data_read).captured(3);
			country = finder.match(data_read).captured(4);
			state = finder.match(data_read).captured(5);
			city = finder.match(data_read).captured(6);
			break;
		}
	}
	QString pic_dir_str = QCoreApplication::applicationDirPath() + "/data/";
	QString season_dir_str = Herodotus::name_text[season];
	season_dir_str.remove(".txt");
	pic_dir_str += season_dir_str + "/";
	pic_dir_str += number + "/";
	QDir pic_dir(pic_dir_str);
	if (!pic_dir.exists()) {
		pic_dir.mkpath(pic_dir.absolutePath());
	}
	pic_dir.setFilter(QDir::Files);
	pic_dir.setSorting(QDir::Name);
//	pic_dir.setNameFilters(QStringList("*.png"));
	list_pics = pic_dir.entryList();
	if (list_pics.size() > 0) {
		current_pic = new QPixmap(list_pics[0]);
	}

	QString title = "Herodotus - Team #" + number + ": " + name;
	this->setWindowTitle(title);

	ui->label_number->setText("Team #" + number);
	ui->label_name->setText(name);
	ui->label_country->setText(country);
	ui->label_state->setText(state);
	ui->label_city->setText(city);
	ui->label_website->setText("<a href=\"" + website + "\">Team Website<\\a>");
	ui->label_pic->setPixmap(*current_pic);

	QObject::connect(	timer_anim,	&QTimer::timeout,
						this,		&DetailsWindow::fwd_pic);
	timer_anim->setInterval(5000);
	timer_anim->start();
}

DetailsWindow::~DetailsWindow()
{
	delete current_pic;
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
