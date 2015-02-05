#ifndef DISPWINDOW_H
#define DISPWINDOW_H

#include <QDebug>

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

private:
	Ui::DispWindow* ui;
};

#endif // DISPWINDOW_H
