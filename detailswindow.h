#ifndef DETAILSWINDOW_H
#define DETAILSWINDOW_H

#include <QDebug>

#include <QTimer>

#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QTextStream>
#include <QPixmap>

#include <QDir>
#include <QFile>

#include <QDialog>

#include "herodotus.h"

namespace Ui {
class DetailsWindow;
}

class DetailsWindow : public QDialog
{
	Q_OBJECT

public:
	explicit DetailsWindow(int current_season, QString team_number, QWidget* parent = 0);
	~DetailsWindow();

private slots:
	void fwd_pic();
	void rev_pic();

	void on_pushButton_L_clicked();
	void on_pushButton_R_clicked();

	void on_pushButton_close_clicked();

private:
	Ui::DetailsWindow *ui;
	QTimer* timer_anim;
	int season;
	QStringList list_pics;
	QPixmap* current_pic;

	QString number;
	QString name;
	QString website;
	QString country;
	QString state;
	QString city;
};

#endif // DETAILSWINDOW_H
