#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

/**
 * @brief Custom button class for easier creation and connection with functions.
 */
class Button : public QToolButton
{
    Q_OBJECT

public:
    /**
   * @brief Constructor for the Button class.
   *
   * @param text displayed
   * @param parent widget
   */
    explicit Button(const QString &text, QWidget *parent = nullptr);
};
#endif
