#ifndef DISPWINDOW_H
#define DISPWINDOW_H

#include <QDebug>

#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QRegularExpression>

#include <QDir>
#include <QFile>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QMainWindow>

#include <QMessageBox>
#include <QProgressDialog>

#include"herodotus.h"

namespace Ui {
class DispWindow;
}

class DispWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DispWindow(QWidget *parent = 0);
	~DispWindow();

//	void add_teams(	QStringList list_added,
//					QStringList number_list,
//					QStringList website_list,
//					QStringList country_list,
//					QStringList state_list,
//					QStringList city_list	);

signals:
//	void download_done(int year);

private slots:
	void clear_table();
	void populate_table(int index);

//	void download_year(int year);
//	void page_downloaded(QNetworkReply* reply);
//	void write_file();

	void on_comboBox_season_currentIndexChanged(int index);

	void on_pushButton_close_clicked();

	void on_pushButton_clear_clicked();
	void on_pushButton_search_clicked();
	void on_pushButton_browse_clicked();

//	void on_pushButton_fetch_clicked();

private:
	Ui::DispWindow* ui;
	QDir dir_program;
//	QNetworkAccessManager* manager;
//	QStringList* list_teams;
	QStandardItemModel* table_teams;

	QStringList* list_numbers;
	QStringList* list_names;
	QStringList* list_websites;
	QStringList* list_countries;
	QStringList* list_states;
	QStringList* list_cities;

//	int page;
//
//	static QString URL_part_I;
//	static QString URL_part_II;
//	static QString URL_part_III;
};

#endif // DISPWINDOW_H
