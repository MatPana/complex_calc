#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

/**
 * @brief Custom button class inheriting from Qt's QToolButton.
 */
class Button : public QToolButton
{
    Q_OBJECT

public:
    /**
   * @brief Constructor for the Button class.
   *
   * @param text text displayed.
   * @param parent parent widget.
   */
    explicit Button(const QString &text, QWidget *parent = nullptr);
};
#endif
