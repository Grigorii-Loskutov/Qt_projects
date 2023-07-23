#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>

class Signals : public QObject
{
    Q_OBJECT
public:
    explicit Signals(QObject *parent = nullptr);

signals:
    void set_Start();
    void set_Stop();
    void set_Lap();
    void set_Clear();
    void set_LapTime(QString lap_time);
};

#endif // SIGNALS_H
