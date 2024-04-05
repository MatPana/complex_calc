#include "calculator.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>
#include <QChart>
#include <QValueAxis>
#include <QChartView>
#include <QScatterSeries>
#include <QMargins>
#include <QMessageBox>

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

    Button *cAreaButton = createButton(tr("Circle Area"), &Calculator::calculateCircleArea);
    Button *cCircButton = createButton(tr("Circle Circumference"), &Calculator::calculateCircleCircumference);
    Button *tAreaButton = createButton(tr("Triangle Area"), &Calculator::calculateTriangleArea);
    Button *tCircButton = createButton(tr("Triangle Circumference"), &Calculator::calculateTriangleCircumference);


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

    mainLayout->addWidget(cAreaButton, 7, 0, 1, 3);
    mainLayout->addWidget(tAreaButton, 7, 3, 1, 3);
    mainLayout->addWidget(cCircButton, 8, 0, 1, 3);
    mainLayout->addWidget(tCircButton, 8, 3, 1, 3);


    // Chart for plotting the results.
    chartView->setChart(chart);
    mainLayout->addWidget(chartView, 0, 7, 9, 5);
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
 * @brief Updates the calculator displays..
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
}

/**
 * @brief Reads the values from the scren of the calculator.
 *
 * @return A ComplexNumber object representing the values displays.
 */
ComplexNumber Calculator::readNumber() {
    double real = std::stod(display->text().toStdString());
    double imaginary = std::stod(display_i->text().toStdString());
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
void Calculator::add()
{
    updateValue();
    operation = "addition";
}

/**
 * @brief Performs subtraction and updates the calculator's state.
 */
void Calculator::subtract()
{
    updateValue();
    operation = "subtraction";
}

/**
 * @brief Performs multiplication and updates the calculator's state.
 */
void Calculator::multiply()
{
    updateValue();
    operation = "multiplication";
}

/**
 * @brief Performs division and updates the calculator's state.
 */
void Calculator::divide()
{
    updateValue();
    operation = "division";
}

/**
 * @brief Performs the operation, displays numeric result and plots it.
 *
 * @throws std::invalid_argument If division by zero occurs.
 */
void Calculator::equals()
{
    bool newPlot = true;
    ComplexNumber read = readNumber();
    ComplexNumber result(0, 0);
    ComplexNumber lastValue = calcMemory.getLast();
    if (operation == "addition") {
        result = read.add(lastValue);
    } else if (operation == "subtraction") {
        result = lastValue.subtract(read);
    }else if (operation == "multiplication") {
        result = read.multiply(lastValue);
    }else if (operation == "division") {
        try {
            result = lastValue.divide(read);
        } catch (std::invalid_argument) {
            result = ComplexNumber(0.0, 0.0);
            QMessageBox::critical(this, "Division error", "Cannot divide by zero!");
            newPlot = false;
        }
    }
    displayNumber(result);
    if (newPlot) {
        updatePlot(lastValue, read, result);
    }
}

/**
 * @brief Calculates the square root, displays it and plots it.
 */
void Calculator::root()
{
    ComplexNumber read = readNumber();
    ComplexNumber output = read.root();

    displayNumber(output);
    updatePlot(read, output);
}

/**
 * @brief Calculates the second power of the number, displays it and plots it.
 */
void Calculator::power()
{
    ComplexNumber read = readNumber();
    ComplexNumber output = read.multiply(read);

    displayNumber(output);
    updatePlot(read, output);
}

/**
 * @brief Calculates the absolute value of the number, displays it and plots it.
 */
void Calculator::absolute()
{
    ComplexNumber read = readNumber();
    ComplexNumber output(read.absoluteValue(), 0.0);

    displayNumber(output);
    updatePlot(read, output);
}

/**
 * @brief Calculates the inverse, displays it and plots it.
 *
 * @throws std::invalid_argument If attempting to take the inverse of zero.
 */
void Calculator::inverse()
{
    bool newPlot = true;
    ComplexNumber read = readNumber();
    ComplexNumber result(0.0, 0.0);

    try {
        result = read.inverse();
    } catch (std::invalid_argument) {
        QMessageBox::critical(this, "Inverse error", "Cannot divide by zero!");
        newPlot = false;
    }

    displayNumber(result);
    if (newPlot) {
        updatePlot(read, result);
    }

}

/**
 * @brief Calculates the conjugate of the number, displays it and plots it.
 */
void Calculator::conjugate()
{
    ComplexNumber read = readNumber();
    ComplexNumber output = read.conjugate();

    displayNumber(output);
    updatePlot(read, output);
}

/**
 * @brief Calculates the circle area, displays it and plots it.
 */
void Calculator::calculateCircleArea() {
    try {
        ComplexNumber input = readNumber();
        double radius = input.getReal();

        if (input.getImaginary() != 0.0) {
            throw std::invalid_argument("Imaginary part must be zero!");
        }

        Circle circle(radius);  // Validation happens here (throws exception for negative radius)
        double area = circle.calculateArea();
        ComplexNumber output(area, 0);
        displayNumber(output);
        updatePlot(input, output);
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Area Error - accepts only positive real numbers!", e.what());
    }
}

/**
 * @brief Calculates the circle circumference, displays it and plots it.
 */
void Calculator::calculateCircleCircumference() {
    ComplexNumber input = readNumber();
    double radius = input.getReal();

    try {
        if (input.getImaginary() != 0.0) {
            throw std::invalid_argument("Imaginary part must be zero!");
        }

        Circle circle(radius);
        double circ = circle.calculateCircumference();
        ComplexNumber output(circ, 0);
        displayNumber(output);
        updatePlot(input, output);  // Update plot after successful calculation
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Area Error - accepts only positive real numbers!", e.what());
    }
}

/**
 * @brief Calculates the triangle area, displays it and plots it.
 */
void Calculator::calculateTriangleArea() {
    try {
        ComplexNumber input = readNumber();
        double side = input.getReal();

        if (input.getImaginary() != 0.0) {
            throw std::invalid_argument("Imaginary part must be zero!");
        }

        Triangle triangle(side);  // Validation happens here (throws exception for negative radius)
        double area = triangle.calculateArea();
        ComplexNumber output(area, 0);
        displayNumber(output);
        updatePlot(input, output);
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Area Error - accepts only positive real numbers!", e.what());
    }
}

/**
 * @brief Calculates the triangle circumference, displays it and plots it.
 */
void Calculator::calculateTriangleCircumference() {
    ComplexNumber input = readNumber();
    double side = input.getReal();

    try {
        if (input.getImaginary() != 0.0) {
            throw std::invalid_argument("Imaginary part must be zero!");
        }

        Triangle triangle(side);
        double circ = triangle.calculateCircumference();
        ComplexNumber output(circ, 0);
        displayNumber(output);
        updatePlot(input, output);  // Update plot after successful calculation
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Area Error - accepts only positive real numbers!", e.what());
    }
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
void Calculator::updatePlot(ComplexNumber a, ComplexNumber b, ComplexNumber r) {
    QScatterSeries *seriesA = new QScatterSeries;
    QScatterSeries *seriesB = new QScatterSeries;
    QScatterSeries *seriesR = new QScatterSeries;
    seriesA->setName("First Value");
    seriesB->setName("Second Value");
    seriesR->setName("Result");

    seriesA->append(a.getReal(), a.getImaginary());
    seriesB->append(b.getReal(), b.getImaginary());
    seriesR->append(r.getReal(), r.getImaginary());

    chart = new QChart;
    chartView = new QChartView(chart);
    mainLayout->addWidget(chartView, 0, 7, 9, 5);
    chartView->setMinimumSize(QSize(400, 300));
    chart->createDefaultAxes();
    chart->addSeries(seriesA);
    chart->addSeries(seriesB);
    chart->addSeries(seriesR);

    double minReal = std::min({a.getReal(), b.getReal(), r.getReal()});
    double maxReal = std::max({a.getReal(), b.getReal(), r.getReal()});
    double minImag = std::min({a.getImaginary(), b.getImaginary(), r.getImaginary()});
    double maxImag = std::max({a.getImaginary(), b.getImaginary(), r.getImaginary()});

    double realRange = maxReal - minReal;
    double imagRange = maxImag - minImag;

    double realMargin = realRange * 0.1;
    double imagMargin = imagRange * 0.1;

    if (realMargin == 0) {
        realMargin = 0.1;
    }
    if (imagMargin == 0) {
        imagMargin = 0.1;
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setRange(minReal - realMargin, maxReal + realMargin);
    chart->axes(Qt::Vertical).back()->setRange(minImag - imagMargin, maxImag + imagMargin);
    chart->axes(Qt::Horizontal).back()->setTitleText("Real Axis");
    chart->axes(Qt::Vertical).back()->setTitleText("Imaginary Axis");
}

/**
 * @brief Updates the plot for a two-value calculation.
 *
 * This method creates a scatter plot with two data points.
 *
 * @param a first number to be plotted.
 * @param r result number to be plotted.
 */
void Calculator::updatePlot(ComplexNumber a, ComplexNumber r) {
    QScatterSeries *seriesA = new QScatterSeries;
    QScatterSeries *seriesR = new QScatterSeries;
    seriesA->setName("Value");
    seriesR->setName("Result");

    seriesA->append(a.getReal(), a.getImaginary());
    seriesR->append(r.getReal(), r.getImaginary());

    chart = new QChart;
    chartView = new QChartView(chart);
    mainLayout->addWidget(chartView, 0, 7, 9, 5);
    chartView->setMinimumSize(QSize(400, 300));
    chart->createDefaultAxes();
    chart->addSeries(seriesA);
    chart->addSeries(seriesR);

    double minReal = std::min({a.getReal(), r.getReal()});
    double maxReal = std::max({a.getReal(), r.getReal()});
    double minImag = std::min({a.getImaginary(), r.getImaginary()});
    double maxImag = std::max({a.getImaginary(), r.getImaginary()});

    double realRange = maxReal - minReal;
    double imagRange = maxImag - minImag;

    double realMargin = realRange * 0.1;
    double imagMargin = imagRange * 0.1;

    if (realMargin == 0) {
        realMargin = 0.1;
    }
    if (imagMargin == 0) {
        imagMargin = 0.1;
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setRange(minReal - realMargin, maxReal + realMargin);
    chart->axes(Qt::Vertical).back()->setRange(minImag - imagMargin, maxImag + imagMargin);
    chart->axes(Qt::Horizontal).back()->setTitleText("Real Axis");
    chart->axes(Qt::Vertical).back()->setTitleText("Imaginary Axis");
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
