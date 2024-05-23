#ifndef PHONENUMBERVALIDATOR_H
#define PHONENUMBERVALIDATOR_H

#include <QValidator>

class PhoneNumberValidator : public QValidator
{
public:
    explicit PhoneNumberValidator(QObject *parent = nullptr);

    // QValidator interface
public:
    State validate(QString &, int &) const;
};

#endif // PHONENUMBERVALIDATOR_H
