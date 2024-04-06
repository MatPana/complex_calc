#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include "complexnumber.h"
#include "calcmemory.h"
#include "shape.h"
#include "calculatoroperation.h"

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
    /**
     * @brief Method handling clicking a number button.
     */
    void digitClicked();

    /**
     * @brief Adds a decimal poin.
     */
    void pointClicked();

    /**
     * @brief Switches the sign of the value in the display.
     */
    void changeSignClicked();

    /**
     * @brief Removes the last digit in the active display.
     */
    void backspaceClicked();

    /**
     * @brief Clears the current value from the active display.
     */
    void clear();

    /**
     * @brief Clears both the real and imaginary displays.
     */
    void clearAll();

    /**
     * @brief Clears the calculator's memory.
     */
    void clearMemory();

    /**
     * @brief Reads the stored complex number from memory and displays it.
     */
    void readMemory();

    /**
     * @brief Reads the stored number from display and remembers it.
     */
    void setMemory();

    /**
     * @brief Reads the stored number from display and ads it to the stored number.
     */
    void addToMemory();

    /**
     * @brief Performs addition and updates the calculator's state.
     */
    void add();

    /**
     * @brief Performs subtraction and updates the calculator's state.
     */
    void subtract();

    /**
     * @brief Performs multiplication and updates the calculator's state.
     */
    void multiply();

    /**
     * @brief Performs division and updates the calculator's state.
     */
    void divide();

    /**
     * @brief Performs the operation, displays numeric result and plots it.
     *
     * @throws std::invalid_argument If division by zero occurs.
     */
    void equals();

    /**
     * @brief Calculates the square root, displays it and plots it.
     */
    void root();

    /**
     * @brief Calculates the second power of the number, displays it and plots it.
     */
    void power();

    /**
     * @brief Calculates the absolute value of the number, displays it and plots it.
     */
    void absolute();

    /**
     * @brief Calculates the inverse, displays it and plots it.
     *
     * @throws std::invalid_argument If attempting to take the inverse of zero.
     */
    void inverse();

    /**
     * @brief Calculates the conjugate of the number, displays it and plots it.
     */
    void conjugate();

    /**
     * @brief Calculates the circle circumference, displays it and plots it.
     */
    void calculateCircleCircumference();

    /**
     * @brief Calculates the circle area, displays it and plots it.
     */
    void calculateCircleArea();

    /**
     * @brief Calculates the triangle circumference, displays it and plots it.
     */
    void calculateTriangleCircumference();

    /**
     * @brief Calculates the triangle area, displays it and plots it.
     */
    void calculateTriangleArea();

    /**
     * @brief Sets the calculator to imaginary number mode.
     *
     * Starts inputing imaginary part of the number.
     */
    void realClicked();

    /**
     * @brief Sets the calculator to real number mode.
     *
     * Starts inputing real part of the number.
     */
    void imgClicked();

    /**
     * @brief Updates the displayed values on both displays.
     */
    void updateValue();

    /**
     * @brief Clears the display.
     *
     * Sets both to zeros.
     */
    void clearDisplay();

    /**
     * @brief Updates the plot for a three-value calculation.
     *
     * This method creates a scatter plot with three data points.
     *
     * @param a first number to be plotted.
     * @param b second number to be plotted.
     * @param r result number to be plotted.
    */
    void updatePlot(ComplexNumber a, ComplexNumber b, ComplexNumber r);

    /**
     * @brief Updates the plot for a two-value calculation.
     *
     * This method creates a scatter plot with two data points.
     *
     * @param a first number to be plotted.
     * @param r result number to be plotted.
    */
    void updatePlot(ComplexNumber a, ComplexNumber r);

    /**
     * @brief Get the currently active display.
     *
     * @return A pointer to the currently active `QLineEdit` object.
     */
    QLineEdit* getActiveDisplay();

    /**
     * @brief Updates the calculator displays..
     *
     * @param a - complex number to be displayed.
     */
    void displayNumber(ComplexNumber a);

    /**
     * @brief Reads the values from the scren of the calculator.
     *
     * @return A ComplexNumber object representing the values displays.
     */
    ComplexNumber readNumber();

private:
    /**
     * @brief Make a new Button object remember the function clicked.
     *
     * @tparam PointerToMemberFunction - pointer to a member function of the Calculator class
     *
     * @return A pointer to the newly created Button object.
    */
    template<typename PointerToMemberFunction>


    Button *createButton(const QString &text, const PointerToMemberFunction &member);

    /**
     * @brief Performs a calculation based on a given operand and pending operator.
     *
     * @param rightOperand right-hand operand to use in the calculation (double).
     * @param pendingOperator The pending operator to be used in the calculation (QString).
     * @return True if the calculation was successful, false otherwise (bool).
     */
    bool calculate(double rightOperand, const QString &pendingOperator);

    // Member variables:

    /**
     *  @brief An object to manage calculator memory (CalcMemory).
     */
    CalcMemory calcMemory;

    /**
     *  @brief Pointer to currently conducted operation.
     */
    std::unique_ptr<CalculatorOperation> currentOperation;

    /**
     * @brief A flag indicating whether the real or imaginary part is currently being edited.
     */
    bool realPart;

    /**
     * @brief The current pending operator (stored as a string).
     */
    std::string operation;

    /**
     * @brief QLineEdits for displaying the real and imaginary parts of a complex number.
     *
     * These QLineEdit objects are used to display the real and imaginary parts.
     */
    QLineEdit *display, *display_i;

    /**
     * @brief Palettes for active and inactive display elements.
     *
     * Control colour setting.
     */
    QPalette palette_active, palette_inactive;

    /**
     * @brief QChart object for visualizing complex number calculations.
     */
    QChart *chart;

    /**
     * @brief QChartView object for displaying the chart visualization.
     */
    QChartView *chartView;

    /**
     * @brief QGridLayout object for managing GUI.
     */
    QGridLayout *mainLayout;

    /**
     * @brief Number of unique digits in decimal system.
     */
    enum { NumDigitButtons = 10 };

    /**
     * @brief Array of Button objects for digits (0-9).
     */
    Button *digitButtons[NumDigitButtons];
};
#endif
