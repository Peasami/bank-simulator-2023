#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include "DLLPinCode_global.h"
#include "pinwindow.h"
#include <QString>
#include <QObject>
#include <QDebug>


class DLLPINCODE_EXPORT DLLPinCode
{
public:
    DLLPinCode();
    void openPinWindow();

private:
    pinwindow *pinOlio;
};

#endif // DLLPINCODE_H
