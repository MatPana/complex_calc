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
    CalcMemory calcMemory;
    palette_active.setColor(QPalette::Base,Qt::green);
    palette_inactive.setColor(QPalette::Base,Qt::white);

    display = new QLineEdit("0");

    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

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


    Button *equalButton = createButton(tr("="), &Calculator::equals);

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


    chartView->setChart(chart);
    mainLayout->addWidget(chartView, 0, 7, 7, 5);
    chartView->setMinimumSize(QSize(400, 300));
    chart->createDefaultAxes();

    setLayout(mainLayout);
    setWindowTitle(tr("Calculator"));
}

void Calculator::realClicked()
{
    realPart = true;

    display->setPalette(palette_active);
    display_i->setPalette(palette_inactive);
\
}

void Calculator::imgClicked()
{
    realPart = false;

    display->setPalette(palette_inactive);
    display_i->setPalette(palette_active);
}

QLineEdit* Calculator::getActiveDisplay()
{
    if (realPart) {
        return display;
    } else {
        return display_i;
    }
}

void Calculator::displayNumber(ComplexNumber a)
{
    double real = a.getReal();
    double imaginary = a.getImaginary();

    display->setText(QString::number(real));
    display_i->setText(QString::number(imaginary));
}

void Calculator::clearDisplay()
{
    display->setText(QString::number(0));
    display_i->setText(QString::number(0));
}

ComplexNumber Calculator::readNumber()
{
    double a = display->text().toDouble();
    double b = display_i->text().toDouble();
    return ComplexNumber(a, b);
}

void Calculator::updateValue()
{
    calcMemory.updateValue(readNumber());

    display->setText(QString::number(0));
    display_i->setText(QString::number(0));
}

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

void Calculator::changeSignClicked()
{
    QLineEdit *disp = getActiveDisplay();

    QString text = disp->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    disp->setText(text);
}

void Calculator::pointClicked()
{
    QLineEdit *disp = getActiveDisplay();

    if (!disp->text().contains('.'))
        disp->setText(disp->text() + tr("."));
}

void Calculator::add()
{
    updateValue();
    operation = "addition";
}

void Calculator::subtract()
{
    updateValue();
    operation = "subtraction";
}

void Calculator::multiply()
{
    updateValue();
    operation = "multiplication";
}

void Calculator::divide()
{
    updateValue();
    operation = "division";
}

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

void Calculator::root()
{
    ComplexNumber read = readNumber();
    ComplexNumber output = read.root();

    displayNumber(output);
    updatePlot(read, output);
}

void Calculator::power()
{
    ComplexNumber read = readNumber();
    ComplexNumber output = read.multiply(read);

    displayNumber(output);
    updatePlot(read, output);
}

void Calculator::absolute()
{
    ComplexNumber read = readNumber();
    ComplexNumber output(read.absoluteValue(), 0.0);

    displayNumber(output);
    updatePlot(read, output);
}

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

void Calculator::conjugate()
{
    ComplexNumber read = readNumber();
    ComplexNumber output = read.conjugate();

    displayNumber(output);
    updatePlot(read, output);
}


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

void Calculator::clear()
{
    QLineEdit *disp = getActiveDisplay();
    disp->setText("0");
}

void Calculator::clearAll()
{
    display->setText("0");
    display_i->setText("0");
}

void Calculator::clearMemory()
{
    calcMemory.clearMemory();
}

void Calculator::readMemory()
{
    ComplexNumber sumInMemory = calcMemory.readMemory();
    display->setText(QString::number(sumInMemory.getReal()));
    display_i->setText(QString::number(sumInMemory.getImaginary()));
}

void Calculator::setMemory()
{
    calcMemory.setMemory(readNumber());
}

void Calculator::addToMemory()
{
    calcMemory.addToMemory(readNumber());
}

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
    mainLayout->addWidget(chartView, 0, 7, 7, 5);
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

void Calculator::updatePlot(ComplexNumber a, ComplexNumber r) {
    QScatterSeries *seriesA = new QScatterSeries;
    QScatterSeries *seriesR = new QScatterSeries;
    seriesA->setName("Value");
    seriesR->setName("Result");

    seriesA->append(a.getReal(), a.getImaginary());
    seriesR->append(r.getReal(), r.getImaginary());

    chart = new QChart;
    chartView = new QChartView(chart);
    mainLayout->addWidget(chartView, 0, 7, 7, 5);
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

template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}
