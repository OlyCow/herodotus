#include "dispwindow.h"
#include "ui_dispwindow.h"

QString DispWindow::URL_part_I		= "http://www.usfirst.org/whats-going-on/teams?page=";
QString DispWindow::URL_part_II		= "&ProgramCode=FTC&Season=";
QString DispWindow::URL_part_III	= "&Country=USA&StateProv=&ZipCode=&Radius=&op=Search&form_build_id=form-Xm8DcuoUUOwF3kOu_EbF0VFedgTJ1zygh72G4ySDMvs&form_id=first_search_teams_form&sort=asc&order=Team%20Number";

DispWindow::DispWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DispWindow),
	dir_program(QDir(QCoreApplication::applicationDirPath())),
	manager(new QNetworkAccessManager(this)),
	list_teams(new QStringList()),
	table_teams(new QStandardItemModel(0, 6)),
	page(0)
{
	ui->setupUi(this);

	QStringList header_labels;
	header_labels.push_back("Number");
	header_labels.push_back("Name");
	header_labels.push_back("Website");
	header_labels.push_back("Country");
	header_labels.push_back("State");
	header_labels.push_back("City");
	table_teams->setHorizontalHeaderLabels(header_labels);

	ui->tableView_main->setModel(table_teams);

	ui->comboBox_rookie->insertSeparator(1);
	ui->comboBox_country->insertSeparator(1);
	ui->comboBox_country->insertSeparator(5);
	ui->comboBox_state->insertSeparator(1);

	dir_program = QCoreApplication::applicationDirPath() + "data/";
	if (!dir_program.exists()) {
		dir_program = QCoreApplication::applicationDirPath();
		dir_program.mkdir("data/");
		dir_program.cd("data/");
	}
	QFile check_exists = dir_program.absolutePath() + "/Cascade Effect.txt";
	if (!check_exists.exists()) {
		check_exists.open(QFile::WriteOnly | QFile::Text);
		QTextStream buf(&check_exists);
		buf.flush();
		check_exists.close();
	}

	QObject::connect(	manager,	&QNetworkAccessManager::finished,
						this,		&DispWindow::page_downloaded);
	QObject::connect(	this,	&DispWindow::download_done,
						this,	&DispWindow::download_year);
}

DispWindow::~DispWindow()
{
	delete table_teams;
	delete list_teams;
	delete manager;
	delete ui;
}

void DispWindow::on_pushButton_close_clicked()
{
	this->close();
}

//void DispWindow::on_pushButton_fetch_clicked()
//{
//	download_year(2014);
//}

void DispWindow::download_year(int year)
{
	QString url_string;
	QTextStream url_stream(&url_string);
	url_stream << URL_part_I;
	url_stream << page;
	url_stream << URL_part_II;
	url_stream << year;
	url_stream << URL_part_III;
	url_stream.flush();
	QUrl url(url_string);
	QNetworkRequest fetch(url);
	manager->get(fetch);
	page++;
}

void DispWindow::page_downloaded(QNetworkReply* reply)
{
	QStringList name_list;
	QStringList number_list;
	QStringList website_list;
	QStringList country_list;
	QStringList state_list;
	QStringList city_list;
	QString data_read;
	for (int i=1; i<=403; i++) {
		data_read = QString(reply->readLine());
		QRegularExpression finder("<td>(.*?)<\\/td><td>(.*?)<\\/td><td>(.*?)<\\/td><td>(.*?)<\\/td><td><a href=\"(.*?)\">(.*?)<\\/a>");
		QString country = finder.match(data_read).captured(1);
		QString state = finder.match(data_read).captured(2);
		QString city = finder.match(data_read).captured(3);
		QString name = finder.match(data_read).captured(4);
		QString website = "www.usfirst.org" + finder.match(data_read).captured(5);
		QString number = finder.match(data_read).captured(6);
		if (i>=269 && i<=293) {
			name_list.push_back(name);
			number_list.push_back(number);
			website_list.push_back(website);
			country_list.push_back(country);
			state_list.push_back(state);
			city_list.push_back(city);
		}
	}
	reply->deleteLater();
	add_teams(	name_list,
				number_list,
				website_list,
				country_list,
				state_list,
				city_list);
	if (page <= 150) {
		emit download_done(2014);
	} else {
		if (page == 151) {
			write_file();
		}
		page = 0;
	}
}

void DispWindow::add_teams(	QStringList name_list,
							QStringList number_list,
							QStringList website_list,
							QStringList country_list,
							QStringList state_list,
							QStringList city_list	)
{
	int init_length = list_teams->length();
	int add_length = name_list.length();
	for (int i=0; i<add_length; i++) {
		list_teams->push_back(number_list[i]);
		table_teams->appendRow(new QStandardItem(number_list[i]));
		table_teams->setItem(init_length+i, 1, new QStandardItem(name_list[i]));
		table_teams->setItem(init_length+i, 2, new QStandardItem(website_list[i]));
		table_teams->setItem(init_length+i, 3, new QStandardItem(country_list[i]));
		table_teams->setItem(init_length+i, 4, new QStandardItem(state_list[i]));
		table_teams->setItem(init_length+i, 5, new QStandardItem(city_list[i]));
	}
}

void DispWindow::write_file()
{
	QFile writer = dir_program.absolutePath() + "/Cascade Effect.txt";
	writer.open(QFile::ReadWrite | QFile::Text | QFile::Append);
	QTextStream buf(&writer);
	buf << "Number,Name,Website,Country,State,City" << endl;
	for (int i=0; i<list_teams->length(); i++) {
		buf << "\"" << table_teams->item(i, 0)->text() << "\",";
		buf << "\"" << table_teams->item(i, 1)->text() << "\",";
		buf << "\"" << table_teams->item(i, 2)->text() << "\",";
		buf << "\"" << table_teams->item(i, 3)->text() << "\",";
		buf << "\"" << table_teams->item(i, 4)->text() << "\",";
		buf << "\"" << table_teams->item(i, 5)->text() << "\"" << endl;
	}
	buf.flush();
	writer.close();
}

void DispWindow::on_pushButton_clear_clicked()
{
	ui->lineEdit_number->setText("");
	ui->lineEdit_name->setText("");
	ui->comboBox_rookie->setCurrentIndex(0);
	ui->comboBox_country->setCurrentIndex(0);
	ui->comboBox_state->setCurrentIndex(0);
	ui->lineEdit_city->setText("");
}

void DispWindow::on_pushButton_search_clicked()
{
}

void DispWindow::on_pushButton_browse_clicked()
{
	this->on_pushButton_clear_clicked();
	this->on_pushButton_search_clicked();
}
