#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include "complexnumber.h"
#include "calcmemory.h"
#include "shape.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE
class Button;

/**
 * @brief Class representing a simple calculator.
 *
 * Class provides both - simple and complex operations on complex number.
 */
class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void digitClicked();
    void pointClicked();
    void changeSignClicked();

    void backspaceClicked();
    void clear();
    void clearAll();

    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();

    void add();
    void subtract();
    void multiply();
    void divide();

    void equals();
    void root();
    void power();
    void absolute();
    void inverse();
    void conjugate();

    void calculateCircleCircumference();
    void calculateCircleArea();
    void calculateTriangleCircumference();
    void calculateTriangleArea();

    void realClicked();
    void imgClicked();
    void updateValue();
    void clearDisplay();
    void updatePlot(ComplexNumber a, ComplexNumber b, ComplexNumber r);
    void updatePlot(ComplexNumber a, ComplexNumber r);
    QLineEdit* getActiveDisplay();
    void displayNumber(ComplexNumber a);
    ComplexNumber readNumber();

private:
    template<typename PointerToMemberFunction>
    Button *createButton(const QString &text, const PointerToMemberFunction &member);
    bool calculate(double rightOperand, const QString &pendingOperator);

    CalcMemory calcMemory;
    bool realPart;
    std::string operation;

    QLineEdit *display, *display_i;
    QPalette palette_active, palette_inactive;
    QChart *chart;
    QChartView *chartView;
    QGridLayout *mainLayout;

    // Number of unique digits in decimal system.
    enum { NumDigitButtons = 10 };
    Button *digitButtons[NumDigitButtons];
};
#endif
