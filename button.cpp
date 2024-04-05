#include "button.h"

/**
 * @brief Constructor for the Button class.
 *
 * @param text displayed on the button (QString).
 * @param parent widget for the button (QWidget*).
 */
Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}
