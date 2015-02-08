#ifndef DETAILSWINDOW_H
#define DETAILSWINDOW_H

#include <QDebug>

#include <QTimer>

#include <QString>
#include <QRegularExpression>

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
	void on_pushButton_close_clicked();

private:
	Ui::DetailsWindow *ui;
	int season;
	QString number;
};

#endif // DETAILSWINDOW_H
