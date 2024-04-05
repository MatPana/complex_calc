#include <QApplication>

#include "calculator.h"

int main(int argc, char *argv[])
{
    // Starting point of the application
    QApplication app(argc, argv);
    Calculator calc;
    calc.show();
    return app.exec();
}
