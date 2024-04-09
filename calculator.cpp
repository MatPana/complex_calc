﻿#include "calculator.h"
#include "button.h"
#include "calculatoroperation.h"

#include <string>
#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QScatterSeries>
#include <QMargins>
#include <QMessageBox>
#include <QFileDialog>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent),
    realPart(true),
    operation("none")
{
    /**
     * @brief Constructor for the Calculator class.
     * @param parent The parent widget of the calculator.
     */
    // Create calculator memory object
    CalcMemory calcMemory;

    /**
     *  @brief Pointer to currently conducted operation.
     */
    std::unique_ptr<CalculatorOperation> currentOperation;

    // Set color palette.
    palette_active.setColor(QPalette::Base,Qt::green);
    palette_inactive.setColor(QPalette::Base,Qt::white);

    // Display to be used for real part of the number.
    display = new QLineEdit("0");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    // Display for imaginary part of the number.
    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    display->setPalette(palette_active);

    display_i = new QLineEdit("0");

    display_i->setReadOnly(true);
    display_i->setAlignment(Qt::AlignRight);
    display_i->setMaxLength(15);

    QFont font_i = display_i->font();
    font_i.setPointSize(font_i.pointSize() + 8);
    display_i->setFont(font_i);

    chartView = new QChartView();
    chart = new QChart;


    // Pointers to buttons executing calculator functions.
    for (int i = 0; i < NumDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);

    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
    Button *changeSignButton = createButton(tr("\302\261"), &Calculator::changeSignClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);

    Button *clearMemoryButton = createButton(tr("MC"), &Calculator::clearMemory);
    Button *readMemoryButton = createButton(tr("MR"), &Calculator::readMemory);
    Button *setMemoryButton = createButton(tr("MS"), &Calculator::setMemory);
    Button *addToMemoryButton = createButton(tr("M+"), &Calculator::addToMemory);

    Button *divisionButton = createButton(tr("\303\267"), &Calculator::divide);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiply);
    Button *minusButton = createButton(tr("-"), &Calculator::subtract);
    Button *plusButton = createButton(tr("+"), &Calculator::add);

    Button *realButton = createButton(tr("Real"), &Calculator::realClicked);
    Button *imgButton = createButton(tr("Imaginary"), &Calculator::imgClicked);

    Button *powerButton = createButton(tr("x\302\262"), &Calculator::power);
    Button *rootButton = createButton(("\u221A"), &Calculator::root);
    Button *conjButton = createButton(tr("x*"), &Calculator::conjugate);
    Button *invButton = createButton(tr("1/x"), &Calculator::inverse);
    Button *absButton = createButton(tr("|x|"), &Calculator::absolute);

    Button *undoButton = createButton(tr("Undo"), &Calculator::undo);
    Button *redoButton = createButton(tr("Redo"), &Calculator::redo);

    Button *showOp1Button = createButton(tr("Operand 1"), &Calculator::showOperand1);
    Button *showOp2Button = createButton(tr("Operand 2"), &Calculator::showOperand2);
    Button *showResButton = createButton(tr("Result"), &Calculator::showResult);

    Button *loadButton = createButton(tr("Load History"), &Calculator::loadHistory);
    Button *saveButton = createButton(tr("Save History"), &Calculator::saveHistory);
    Button *clearHButton = createButton(tr("Clear History"), &Calculator::clearHistory);

    Button *equalButton = createButton(tr("="), &Calculator::equals);

    // GUI setup.
    mainLayout = new QGridLayout;

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(display, 0, 0, 1, 3);
    mainLayout->addWidget(display_i, 0, 3, 1, 3);

    mainLayout->addWidget(realButton, 1, 0, 1, 3);
    mainLayout->addWidget(imgButton, 1, 3, 1, 3);

    mainLayout->addWidget(absButton, 2, 0);
    mainLayout->addWidget(conjButton, 2, 1);
    mainLayout->addWidget(backspaceButton, 2, 3);
    mainLayout->addWidget(clearButton, 2, 4);
    mainLayout->addWidget(clearAllButton, 2, 5);

    mainLayout->addWidget(powerButton, 2, 2);
    mainLayout->addWidget(rootButton, 3,5);
    mainLayout->addWidget(equalButton, 5, 5, 2, 1);
    mainLayout->addWidget(invButton, 4, 5);

    mainLayout->addWidget(clearMemoryButton, 3, 0);
    mainLayout->addWidget(readMemoryButton, 4, 0);
    mainLayout->addWidget(setMemoryButton, 5, 0);
    mainLayout->addWidget(addToMemoryButton, 6, 0);

    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 3;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 6, 1);
    mainLayout->addWidget(pointButton, 6, 2);
    mainLayout->addWidget(changeSignButton, 6, 3);

    mainLayout->addWidget(divisionButton, 3, 4);
    mainLayout->addWidget(timesButton, 4, 4);
    mainLayout->addWidget(minusButton, 5, 4);
    mainLayout->addWidget(plusButton, 6, 4);

    mainLayout->addWidget(undoButton, 7, 0, 1, 3);
    mainLayout->addWidget(redoButton, 7, 3, 1, 3);

    mainLayout->addWidget(showOp1Button, 8, 0, 1, 2);
    mainLayout->addWidget(showOp2Button, 8, 2, 1, 2);
    mainLayout->addWidget(showResButton, 8, 4, 1, 2);

    mainLayout->addWidget(loadButton, 9, 0, 1, 2);
    mainLayout->addWidget(saveButton, 9, 2, 1, 2);
    mainLayout->addWidget(clearHButton, 9, 4, 1, 2);


    // Chart for plotting the results.
    chartView->setChart(chart);
    mainLayout->addWidget(chartView, 0, 7, 10, 5);
    chartView->setMinimumSize(QSize(400, 300));
    chart->createDefaultAxes();

    setLayout(mainLayout);
    setWindowTitle(tr("Calculator"));
}

/**
 * @brief Sets the calculator to real number mode.
 *
 * Starts inputing real part of the number.
 */
void Calculator::realClicked()
{
    realPart = true;

    display->setPalette(palette_active);
    display_i->setPalette(palette_inactive);
\
}

/**
 * @brief Sets the calculator to imaginary number mode.
 *
 * Starts inputing imaginary part of the number.
 */
void Calculator::imgClicked()
{
    realPart = false;

    display->setPalette(palette_inactive);
    display_i->setPalette(palette_active);
}

/**
 * @brief Get the currently active display.
 *
 * @return A pointer to the currently active `QLineEdit` object.
 */
QLineEdit* Calculator::getActiveDisplay()
{
    if (realPart) {
        return display;
    } else {
        return display_i;
    }
}

/**
 * @brief Updates the calculator displays.
 *
 * @param a - complex number to be displayed.
 */
void Calculator::displayNumber(ComplexNumber a)
{
    double real = a.getReal();
    double imaginary = a.getImaginary();

    display->setText(QString::number(real));
    display_i->setText(QString::number(imaginary));
}

/**
 * @brief Clears the display.
 *
 * Sets both to zeros.
 */
void Calculator::clearDisplay()
{
    display->setText(QString::number(0));
    display_i->setText(QString::number(0));
    clearPlot();
}

/**
 * @brief Reads the values from the scren of the calculator.
 *
 * @return A ComplexNumber object representing the values displays.
 */
ComplexNumber Calculator::readNumber() {
    double real = std::stod(display->text().toStdString());
    double imaginary = std::stod(display_i->text().toStdString());
    realClicked();
    return ComplexNumber(real, imaginary);
}

/**
 * @brief Updates the displayed values on both displays.
 */
void Calculator::updateValue()
{
    calcMemory.updateValue(readNumber());

    display->setText(QString::number(0));
    display_i->setText(QString::number(0));
    realClicked();
}

/**
 * @brief Method handling clicking a number button.
 */
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();

    QLineEdit *disp = getActiveDisplay();

    QString operand = disp->text();

    if (operand == "0") {
        operand = "";
    }

    disp->setText(operand + QString::number(digitValue));
}

/**
 * @brief Switches the sign of the value in the display.
 */
void Calculator::changeSignClicked() {
    QLineEdit *disp = getActiveDisplay();
    std::string text = disp->text().toStdString();

    if (text[0] == '-') {
        text.erase(0, 1);
    } else {
        text.insert(0, "-");
    }

    disp->setText(QString::fromStdString(text));
}

/**
 * @brief Adds a decimal poin.
 */
void Calculator::pointClicked()
{
    QLineEdit *disp = getActiveDisplay();

    if (!disp->text().contains('.'))
        disp->setText(disp->text() + tr("."));
}

/**
 * @brief Performs addition and updates the calculator's state.
 */
void Calculator::add() {
    currentOperation = std::make_unique<AdditionOperation>();
    updateValue();
}

/**
 * @brief Performs subtraction and updates the calculator's state.
 */
void Calculator::subtract()
{
    currentOperation = std::make_unique<SubtractionOperation>();
    updateValue();
}

/**
 * @brief Performs multiplication and updates the calculator's state.
 */
void Calculator::multiply()
{
    currentOperation = std::make_unique<MultiplicationOperation>();
    updateValue();
}

/**
 * @brief Performs division and updates the calculator's state.
 */
void Calculator::divide()
{
    currentOperation = std::make_unique<DivisionOperation>();
    updateValue();
}

/**
 * @brief Performs the operation, displays numeric result and plots it.
 *
 * @throws std::invalid_argument If division by zero occurs.
 */
void Calculator::equals() {
    try {
        ComplexNumber read = readNumber();
        ComplexNumber last = calcMemory.getLast();
        if (currentOperation) {
            ComplexNumber result = currentOperation->performOperation(last, &read);

            displayNumber(result);
            updatePlot(last, read, result, currentOperation->serialize());

            historyManager.addOperation(std::move(currentOperation), result, last, &read);
            historyIndex = historyManager.getHistorySize() - 1;
        }
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Operation Error", e.what());
    }
}

/**
 * @brief Calculates the square root, displays it and plots it.
 */
void Calculator::root() {
    ComplexNumber read = readNumber();
    std::unique_ptr<CalculatorOperation> operation = std::make_unique<RootOperation>();

    ComplexNumber result = operation->performOperation(read, nullptr);

    historyManager.addOperation(std::make_unique<RootOperation>(), result, read);

    displayNumber(result);
    updatePlot(read, result, operation->serialize());
}

/**
 * @brief Calculates the second power of the number, displays it and plots it.
 */
void Calculator::power()
{
    ComplexNumber read = readNumber();
    std::unique_ptr<CalculatorOperation> operation = std::make_unique<SquareOperation>();

    ComplexNumber result = operation->performOperation(read, nullptr);

    historyManager.addOperation(std::make_unique<SquareOperation>(), result, read);

    displayNumber(result);
    updatePlot(read, result, operation->serialize());
}

/**
 * @brief Calculates the absolute value of the number, displays it and plots it.
 */
void Calculator::absolute()
{
    ComplexNumber read = readNumber();
    std::unique_ptr<CalculatorOperation> operation = std::make_unique<AbsoluteValueOperation>();

    ComplexNumber output = operation->performOperation(read, nullptr);

    historyManager.addOperation(std::make_unique<AbsoluteValueOperation>(), output, read);

    displayNumber(output);
    updatePlot(read, output, operation->serialize());
}

/**
 * @brief Calculates the inverse, displays it and plots it.
 *
 * @throws std::invalid_argument If attempting to take the inverse of zero.
 */
void Calculator::inverse() {
    ComplexNumber read = readNumber();
    std::unique_ptr<CalculatorOperation> operation = std::make_unique<InverseOperation>();

    try {
        ComplexNumber result = operation->performOperation(read, nullptr);
        historyManager.addOperation(std::make_unique<InverseOperation>(), result, read);

        displayNumber(result);
        updatePlot(read, result, operation->serialize());
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Inverse error", e.what());
    }
}

/**
 * @brief Calculates the conjugate of the number, displays it and plots it.
 */
void Calculator::conjugate()
{
    ComplexNumber read = readNumber();
    std::unique_ptr<CalculatorOperation> operation = std::make_unique<ConjugateOperation>();

    ComplexNumber output = operation->performOperation(read, nullptr);

    historyManager.addOperation(std::make_unique<ConjugateOperation>(), output, read);


    displayNumber(output);
    updatePlot(read, output, operation->serialize());
}

/**
 * @brief Removes the last digit in the active display.
 */
void Calculator::backspaceClicked()
{
    QLineEdit *disp = getActiveDisplay();
    QString text = disp->text();

    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
    }
    disp->setText(text);
}

/**
 * @brief Clears the current value from the active display.
 */
void Calculator::clear()
{
    QLineEdit *disp = getActiveDisplay();
    disp->setText("0");
}

/**
 * @brief Clears both the real and imaginary displays.
 */
void Calculator::clearAll()
{
    display->setText("0");
    display_i->setText("0");
    clearPlot();
}

/**
 * @brief Clears the calculator's memory.
 */
void Calculator::clearMemory()
{
    calcMemory.clearMemory();
}

/**
 * @brief Reads the stored complex number from memory and displays it.
 */
void Calculator::readMemory()
{
    ComplexNumber sumInMemory = calcMemory.readMemory();
    display->setText(QString::number(sumInMemory.getReal()));
    display_i->setText(QString::number(sumInMemory.getImaginary()));
}

/**
 * @brief Reads the stored number from display and remembers it.
 */
void Calculator::setMemory()
{
    calcMemory.setMemory(readNumber());
}

/**
 * @brief Reads the stored number from display and ads it to the stored number.
 */
void Calculator::addToMemory()
{
    calcMemory.addToMemory(readNumber());
}

/**
 * @brief Updates the plot for a three-value calculation.
 *
 * This method creates a scatter plot with three data points.
 *
 * @param a first number to be plotted.
 * @param b second number to be plotted.
 * @param r result number to be plotted.
 */
void Calculator::updatePlot(const ComplexNumber& a, const ComplexNumber& b, const ComplexNumber& r, const std::string& operationType) {
    QScatterSeries *seriesA = new QScatterSeries;
    QScatterSeries *seriesB = new QScatterSeries;
    QScatterSeries *seriesR = new QScatterSeries;
    seriesA->setName("First Value");
    seriesB->setName("Second Value");
    seriesR->setName("Result");

    seriesA->append(a.getReal(), a.getImaginary());
    seriesB->append(b.getReal(), b.getImaginary());
    seriesR->append(r.getReal(), r.getImaginary());

    chart->removeAllSeries();

    chart->setTitle(QString::fromStdString(operationType));
    chart->addSeries(seriesA);
    chart->addSeries(seriesB);
    chart->addSeries(seriesR);
    chart->createDefaultAxes();


    double minReal = std::min({a.getReal(), b.getReal(), r.getReal()});
    double maxReal = std::max({a.getReal(), b.getReal(), r.getReal()});
    double minImag = std::min({a.getImaginary(), b.getImaginary(), r.getImaginary()});
    double maxImag = std::max({a.getImaginary(), b.getImaginary(), r.getImaginary()});

    adjustAxes(minReal, maxReal, minImag, maxImag);
}

/**
 * @brief Updates the plot for a two-value calculation.
 *
 * This method creates a scatter plot with two data points.
 *
 * @param a first number to be plotted.
 * @param r result number to be plotted.
 */
void Calculator::updatePlot(const ComplexNumber& a, const ComplexNumber& r, const std::string& operationType) {
    QScatterSeries *seriesA = new QScatterSeries;
    QScatterSeries *seriesR = new QScatterSeries;
    seriesA->setName("Value");
    seriesR->setName("Result");

    seriesA->append(a.getReal(), a.getImaginary());
    seriesR->append(r.getReal(), r.getImaginary());

    chart->removeAllSeries();

    chart->setTitle(QString::fromStdString(operationType));
    chart->addSeries(seriesA);
    chart->addSeries(seriesR);
    chart->createDefaultAxes();


    double minReal = std::min({a.getReal(), r.getReal()});
    double maxReal = std::max({a.getReal(), r.getReal()});
    double minImag = std::min({a.getImaginary(), r.getImaginary()});
    double maxImag = std::max({a.getImaginary(), r.getImaginary()});

    adjustAxes(minReal, maxReal, minImag, maxImag);
}

/**
 * @brief Adjust axes to center display and adjust "magnification".
 *
 * @param minReal - minimal real value to plot
 * @param maxReal - maximal real value to plot
 * @param minImag - minimal imaginary value to plot
 * @param maxImag - maximal imaginary value to plot
 */
void Calculator::adjustAxes(double minReal, double maxReal, double minImag, double maxImag) {
    double realRange = maxReal - minReal;
    double imagRange = maxImag - minImag;

    double realMargin = (realRange == 0) ? 0.1 : realRange * 0.1;
    double imagMargin = (imagRange == 0) ? 0.1 : imagRange * 0.1;

    chart->axes(Qt::Horizontal).back()->setRange(minReal - realMargin, maxReal + realMargin);
    chart->axes(Qt::Vertical).back()->setRange(minImag - imagMargin, maxImag + imagMargin);
    chart->axes(Qt::Horizontal).back()->setTitleText("Real Axis");
    chart->axes(Qt::Vertical).back()->setTitleText("Imaginary Axis");
}

/**
 * @brief Clear plot display.
 */
void Calculator::clearPlot() {
    if (chart != nullptr) {
        // Remove all series from the chart
        QList<QAbstractSeries *> allSeries = chart->series();
        for (QAbstractSeries *series : allSeries) {
            chart->removeSeries(series);
            delete series;
        }

        chart->setTitle("Cleared");
        chart->createDefaultAxes();
        chart->axes(Qt::Horizontal).back()->setTitleText("Real Axis");
        chart->axes(Qt::Vertical).back()->setTitleText("Imaginary Axis");

        chartView->repaint();
    }
}

/**
 * @brief Make a new Button object remember the function clicked.
 *
 * @tparam PointerToMemberFunction - pointer to a member function of the Calculator class
 *
 * @return A pointer to the newly created Button object.
 */
template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}

/**
 * @brief Revert one step back in history.
 */
void Calculator::undo() {
    if (historyIndex > 0) { // There is a history.
        historyIndex--;
        const auto& entry = historyManager.getHistoryEntry(historyIndex);
        if (entry.operation->isUnary()) {
            updatePlot(entry.operand1, entry.result, entry.operation->serialize());
        } else {
            updatePlot(entry.operand1, entry.operand2, entry.result, entry.operation->serialize());
        }
        displayNumber(entry.result);
    }

}

/**
 * @brief Move forward one step back in history.
 */
void Calculator::redo() {
    int historySize = historyManager.getHistorySize();
    if (historyIndex < historySize - 1) { // There is "future" to move to.
        historyIndex++;
        const auto& entry = historyManager.getHistoryEntry(historyIndex);
        if (entry.operation->isUnary()) {
            updatePlot(entry.operand1, entry.result, entry.operation->serialize());
        } else {
            updatePlot(entry.operand1, entry.operand2, entry.result, entry.operation->serialize());
        }

        displayNumber(entry.result);
    }
}

/**
 * @brief Save operation result to file.
 */
void Calculator::saveHistory() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save history", "", "Text file (*.txt)");
    if (!filePath.isEmpty()) {
        try {
            historyManager.saveHistoryToFile(filePath.toStdString());
        } catch (const std::runtime_error& e) {
            QMessageBox::critical(this, "Error saving.", e.what());
        }
    }
}

/**
 * @brief Load history from a file.
 */
void Calculator::loadHistory() {
    QString filePath = QFileDialog::getOpenFileName(this, "Load history", "", "Text fuke (*.txt)");
    if (!filePath.isEmpty()) {
        try {
            historyManager.loadHistoryFromFile(filePath.toStdString());
            historyIndex = historyManager.getHistorySize() - 1;

            if (historyIndex >= 0) {
                const auto& lastEntry = historyManager.getHistoryEntry(historyIndex);
                displayNumber(lastEntry.result);
                if (lastEntry.operation->isUnary()) {
                    updatePlot(lastEntry.operand1, lastEntry.result, lastEntry.operation->serialize());
                } else {
                    updatePlot(lastEntry.operand1, lastEntry.operand2, lastEntry.result, lastEntry.operation->serialize());
                }
            }
        } catch (const std::runtime_error& e) {
            QMessageBox::critical(this, "Error loading.", e.what());
        }
    }
}

/**
 * @brief Clear calculation history.
 */
void Calculator::clearHistory() {
    historyManager.clearHistory();
    historyIndex = -1;
    clearDisplay();
    clearPlot();
}

/**
 * @brief Switch showing to operand one when browsing history.
 */
void Calculator::showOperand1() {
    if (historyManager.getHistorySize() > 0 && historyIndex >= 0 && historyIndex < historyManager.getHistorySize()) {
        const auto& lastEntry = historyManager.getHistoryEntry(historyIndex);
        displayNumber(lastEntry.operand1);
    } else {
        QMessageBox::information(this, "History", "No history to display.");
    }
}

/**
 * @brief Switch showing to operand two when browsing history.
 */
void Calculator::showOperand2() {
    if (historyManager.getHistorySize() > 0 && historyIndex >= 0 && historyIndex < historyManager.getHistorySize()) {
        const auto& lastEntry = historyManager.getHistoryEntry(historyIndex);
        if (lastEntry.operation->isUnary()) {
            QMessageBox::information(this, "Unary Operation", "The second operand is not available for unary operations.");
        } else {
            displayNumber(lastEntry.operand2);
        }
    } else {
        QMessageBox::information(this, "History", "No history to display.");
    }
}

/**
 * @brief Switch showing to result when browsing history.
 */
void Calculator::showResult() {
    if (historyManager.getHistorySize() > 0 && historyIndex >= 0 && historyIndex < historyManager.getHistorySize()) {
        const auto& lastEntry = historyManager.getHistoryEntry(historyIndex);
        displayNumber(lastEntry.result);
    } else {
        QMessageBox::information(this, "History", "No history to display.");
    }
}
