#include "dispwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DispWindow w;
	w.show();

	return a.exec();
}
