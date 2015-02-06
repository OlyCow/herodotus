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

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include <QMainWindow>

namespace Ui {
class DispWindow;
}

class DispWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DispWindow(QWidget *parent = 0);
	~DispWindow();

	void add_teams(	QStringList list_added,
					QStringList number_list,
					QStringList website_list,
					QStringList country_list,
					QStringList state_list,
					QStringList city_list	);

signals:
	void download_done(int year);

private slots:
	void download_year(int year);
	void page_downloaded(QNetworkReply* reply);

	void on_pushButton_fetch_clicked();

private:
	Ui::DispWindow* ui;
	QNetworkAccessManager* manager;
	QStringList* list_teams;
	QStandardItemModel* table_teams;

	int page;

	static QString URL_part_I;
	static QString URL_part_II;
	static QString URL_part_III;
};

#endif // DISPWINDOW_H
