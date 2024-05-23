#include <QRegularExpression>

#include "phonenumbervalidator.h"

PhoneNumberValidator::PhoneNumberValidator(QObject *parent)
    : QValidator{parent} {}

QValidator::State PhoneNumberValidator::validate(QString& input, int&) const
{
    static QRegularExpression regExpPart("^[0-9]{0,11}$");
    static QRegularExpression regExpFull("^[0-9]{11}$");
    if (!regExpFull.match(input).hasMatch()) {
        if (regExpPart.match(input).hasMatch()) {
            return Intermediate;
        } else {
            if (input.size() > 11) {
                input = input.sliced(0, 11);
            }
            return Invalid;
        }
    } else {
        return Acceptable;
    }
}
