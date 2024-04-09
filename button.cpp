#include "button.h"

/**
 * @brief Constructor for the Button class.
 *
 * @param text displayed
 * @param parent widget
 */
Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}
