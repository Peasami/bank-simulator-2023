/*
 * Tämä luokka on (testi)Tilitapahtumien kirjaamista varten
 */
#ifndef RIVI_H
#define RIVI_H

#include <QObject>


class rivi : public QObject
{
public:
    rivi();
    QString getTime() const;
    void setTime(const QString newTime);

    QString getEvent() const;
    void setEvent(const QString newEvent);

    QString getMaara() const;
    void setMaara(const QString newMaara);

private:
    QString time;   // Tapahtuman aika
    QString event;  // Tapahtuman nimi/tyyppi
    QString maara;  // Tapahtumaan liittyva rahasumma
};

#endif // RIVI_H
