#include "dispwindow.h"
#include "ui_dispwindow.h"

//QString DispWindow::URL_part_I		= "http://www.usfirst.org/whats-going-on/teams?page=";
//QString DispWindow::URL_part_II		= "&ProgramCode=FTC&Season=";
//QString DispWindow::URL_part_III	= "&Country=USA&StateProv=&ZipCode=&Radius=&op=Search&form_build_id=form-Xm8DcuoUUOwF3kOu_EbF0VFedgTJ1zygh72G4ySDMvs&form_id=first_search_teams_form&sort=asc&order=Team%20Number";

DispWindow::DispWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::DispWindow),
	dir_program(QDir(QCoreApplication::applicationDirPath())),
//	manager(new QNetworkAccessManager(this)),
//	list_teams(new QStringList()),
	table_teams(new QStandardItemModel(0, 6)),
//	page(0),
	list_numbers(new QStringList()),
	list_names(new QStringList()),
	list_websites(new QStringList()),
	list_countries(new QStringList()),
	list_states(new QStringList()),
	list_cities(new QStringList())
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
	ui->tableView_main->setColumnWidth(0, 60);
	ui->tableView_main->setColumnWidth(1, 210);
	ui->tableView_main->setColumnWidth(2, 160);
	ui->tableView_main->setColumnWidth(3, 75);
	ui->tableView_main->setColumnWidth(4, 36);
	ui->tableView_main->setColumnWidth(5, 135);

	QObject::connect(	ui->tableView_main,	&QTableView::doubleClicked,
						this,				&DispWindow::showTeamDetails);

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
	QFile data_file(QString(dir_program.absolutePath() + Herodotus::name_text[0]));
	if (!data_file.exists()) {
		data_file.open(QFile::WriteOnly | QFile::Text);
		QTextStream buf(&data_file);
		buf.flush();
		data_file.close();
	}
	data_file.open(QFile::ReadOnly | QFile::Text);
	QTextStream buf(&data_file);
	QString data_read = buf.readLine();
	while (!buf.atEnd()) {
		data_read = buf.readLine();
		QRegularExpression finder("\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\"");
		list_numbers->push_back(finder.match(data_read).captured(1));
		list_names->push_back(finder.match(data_read).captured(2));
		list_websites->push_back(finder.match(data_read).captured(3));
		list_countries->push_back(finder.match(data_read).captured(4));
		list_states->push_back(finder.match(data_read).captured(5));
		list_cities->push_back(finder.match(data_read).captured(6));
	}

	for (int i=0; i<list_numbers->length(); i++) {
		table_teams->appendRow(new QStandardItem(list_numbers->at(i)));
		table_teams->setItem(i, 1, new QStandardItem(list_names->at(i)));
		table_teams->setItem(i, 2, new QStandardItem(list_websites->at(i)));
		table_teams->setItem(i, 3, new QStandardItem(list_countries->at(i)));
		table_teams->setItem(i, 4, new QStandardItem(list_states->at(i)));
		table_teams->setItem(i, 5, new QStandardItem(list_cities->at(i)));
	}

//	QObject::connect(	manager,	&QNetworkAccessManager::finished,
//						this,		&DispWindow::page_downloaded);
//	QObject::connect(	this,	&DispWindow::download_done,
//						this,	&DispWindow::download_year);
}

DispWindow::~DispWindow()
{
	delete list_numbers;
	delete list_names;
	delete list_websites;
	delete list_countries;
	delete list_states;
	delete list_cities;

	delete table_teams;
//	delete list_teams;
//	delete manager;
	delete ui;
}

void DispWindow::showTeamDetails(QModelIndex table_index)
{
	QString team_number = table_teams->item(table_index.row())->text();
	DetailsWindow* detailsWindow = new DetailsWindow(ui->comboBox_season->currentIndex(), team_number, 0);
	detailsWindow->show();
}

void DispWindow::clear_table()
{
	table_teams->removeRows(0,table_teams->rowCount());
	int team_count = list_numbers->length();
	for (int i=0; i<team_count; i++) {
		list_numbers->pop_back();
		list_names->pop_back();
		list_websites->pop_back();
		list_countries->pop_back();
		list_states->pop_back();
		list_cities->pop_back();
	}
}
void DispWindow::populate_table(int index)
{
	QFile data_file(QString(dir_program.absolutePath() + Herodotus::name_text[index]));
	if (!data_file.exists()) {
		data_file.open(QFile::WriteOnly | QFile::Text);
		QTextStream buf(&data_file);
		buf.flush();
		data_file.close();
	}
	data_file.open(QFile::ReadOnly | QFile::Text);
	QTextStream buf(&data_file);
	QString data_read = buf.readLine();
	while (!buf.atEnd()) {
		data_read = buf.readLine();
		QRegularExpression finder("\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\",\"(.*?)\"");
		list_numbers->push_back(finder.match(data_read).captured(1));
		list_names->push_back(finder.match(data_read).captured(2));
		list_websites->push_back(finder.match(data_read).captured(3));
		list_countries->push_back(finder.match(data_read).captured(4));
		list_states->push_back(finder.match(data_read).captured(5));
		list_cities->push_back(finder.match(data_read).captured(6));
	}
	for (int i=0; i<list_numbers->length(); i++) {
		table_teams->appendRow(new QStandardItem(list_numbers->at(i)));
		table_teams->setItem(i, 1, new QStandardItem(list_names->at(i)));
		table_teams->setItem(i, 2, new QStandardItem(list_websites->at(i)));
		table_teams->setItem(i, 3, new QStandardItem(list_countries->at(i)));
		table_teams->setItem(i, 4, new QStandardItem(list_states->at(i)));
		table_teams->setItem(i, 5, new QStandardItem(list_cities->at(i)));
	}
}

void DispWindow::on_comboBox_season_currentIndexChanged(int index)
{
	clear_table();
	populate_table(index);
}

void DispWindow::on_pushButton_close_clicked()
{
	this->close();
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
	table_teams->removeRows(0,table_teams->rowCount());
	std::vector<int> result_indices;
	QString number_search = ui->lineEdit_number->text();
	QString name_search = ui->lineEdit_name->text();
	QString city_search = ui->lineEdit_city->text();
	QStringList name_parts;
	QRegularExpression finder("\\b(?:\\W|[0-9])*(\\w+)\\b");
	QString name_copy = name_search;
	QString match = "test";
	while (match != "") {
		match = finder.match(name_copy).captured(1);
		name_copy.remove(match);
		if (match != ""){
			name_parts.push_back(match);
		}
	}
	QString aggregate = number_search + name_search + city_search;
	for (int i=0; i<list_numbers->size(); i++) {
		if (number_search != "" && number_search == list_numbers->at(i)) {
			result_indices.push_back(i);
		} else if (name_search != "") {
			if (name_search == list_names->at(i)) {
				result_indices.push_back(i);
			}
			for (int j=0; j<name_parts.size(); j++) {
				if (list_names->at(i).contains(name_parts[j], Qt::CaseInsensitive)) {
					result_indices.push_back(i);
				}
			}
		}
		if (aggregate == "") {
			result_indices.push_back(i);
		}
	}
	for (unsigned int i=0; i<result_indices.size(); i++) {
		table_teams->appendRow(new QStandardItem(list_numbers->at(result_indices[i])));
		table_teams->setItem(i, 1, new QStandardItem(list_names->at(result_indices[i])));
		table_teams->setItem(i, 2, new QStandardItem(list_websites->at(result_indices[i])));
		table_teams->setItem(i, 3, new QStandardItem(list_countries->at(result_indices[i])));
		table_teams->setItem(i, 4, new QStandardItem(list_states->at(result_indices[i])));
		table_teams->setItem(i, 5, new QStandardItem(list_cities->at(result_indices[i])));
	}
}
void DispWindow::on_pushButton_browse_clicked()
{
	this->on_pushButton_clear_clicked();
	this->on_pushButton_search_clicked();
}

//void DispWindow::on_pushButton_fetch_clicked()
//{
//	download_year(2014);
//}

//void DispWindow::download_year(int year)
//{
//	QString url_string;
//	QTextStream url_stream(&url_string);
//	url_stream << URL_part_I;
//	url_stream << page;
//	url_stream << URL_part_II;
//	url_stream << year;
//	url_stream << URL_part_III;
//	url_stream.flush();
//	QUrl url(url_string);
//	QNetworkRequest fetch(url);
//	manager->get(fetch);
//	page++;
//}

//void DispWindow::page_downloaded(QNetworkReply* reply)
//{
//	QStringList name_list;
//	QStringList number_list;
//	QStringList website_list;
//	QStringList country_list;
//	QStringList state_list;
//	QStringList city_list;
//	QString data_read;
//	for (int i=1; i<=403; i++) {
//		data_read = QString(reply->readLine());
//		QRegularExpression finder("<td>(.*?)<\\/td><td>(.*?)<\\/td><td>(.*?)<\\/td><td>(.*?)<\\/td><td><a href=\"(.*?)\">(.*?)<\\/a>");
//		QString country = finder.match(data_read).captured(1);
//		QString state = finder.match(data_read).captured(2);
//		QString city = finder.match(data_read).captured(3);
//		QString name = finder.match(data_read).captured(4);
//		QString website = "www.usfirst.org" + finder.match(data_read).captured(5);
//		QString number = finder.match(data_read).captured(6);
//		if (i>=269 && i<=293) {
//			name_list.push_back(name);
//			number_list.push_back(number);
//			website_list.push_back(website);
//			country_list.push_back(country);
//			state_list.push_back(state);
//			city_list.push_back(city);
//		}
//	}
//	reply->deleteLater();
//	add_teams(	name_list,
//				number_list,
//				website_list,
//				country_list,
//				state_list,
//				city_list);
//	if (page <= 150) {
//		emit download_done(2014);
//	} else {
//		if (page == 151) {
//			write_file();
//		}
//		page = 0;
//	}
//}

//void DispWindow::add_teams(	QStringList name_list,
//							QStringList number_list,
//							QStringList website_list,
//							QStringList country_list,
//							QStringList state_list,
//							QStringList city_list	)
//{
//	int init_length = list_teams->length();
//	int add_length = name_list.length();
//	for (int i=0; i<add_length; i++) {
//		list_teams->push_back(number_list[i]);
//		table_teams->appendRow(new QStandardItem(number_list[i]));
//		table_teams->setItem(init_length+i, 1, new QStandardItem(name_list[i]));
//		table_teams->setItem(init_length+i, 2, new QStandardItem(website_list[i]));
//		table_teams->setItem(init_length+i, 3, new QStandardItem(country_list[i]));
//		table_teams->setItem(init_length+i, 4, new QStandardItem(state_list[i]));
//		table_teams->setItem(init_length+i, 5, new QStandardItem(city_list[i]));
//	}
//}

//void DispWindow::write_file()
//{
//	QFile writer = dir_program.absolutePath() + "/Cascade Effect.txt";
//	writer.open(QFile::ReadWrite | QFile::Text | QFile::Append);
//	QTextStream buf(&writer);
//	buf << "Number,Name,Website,Country,State,City" << endl;
//	for (int i=0; i<list_teams->length(); i++) {
//		buf << "\"" << table_teams->item(i, 0)->text() << "\",";
//		buf << "\"" << table_teams->item(i, 1)->text() << "\",";
//		buf << "\"" << table_teams->item(i, 2)->text() << "\",";
//		buf << "\"" << table_teams->item(i, 3)->text() << "\",";
//		buf << "\"" << table_teams->item(i, 4)->text() << "\",";
//		buf << "\"" << table_teams->item(i, 5)->text() << "\"" << endl;
//	}
//	buf.flush();
//	writer.close();
//}
