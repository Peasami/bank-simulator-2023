
#include "rivi.h"

rivi::rivi()
{

}

QString rivi::getTime() const
{
    return time;
}

void rivi::setTime(const QString &newTime)
{
    time = newTime;
}

QString rivi::getEvent() const
{
    return event;
}

void rivi::setEvent(const QString &newEvent)
{
    event = newEvent;
}

QString rivi::getMaara() const
{
    return maara;
}

void rivi::setMaara(const QString &newMaara)
{
    maara = newMaara;
}

