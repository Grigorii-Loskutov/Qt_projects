#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>
#include <QDateTime>

class Stopwatch : public QObject {
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);
    bool isRunning() const;
    int getTime() const;
    int getLapTime();

signals:
    void timeUpdated(int time);

public slots:
    void start();
    void stop();
    void reset();

private slots:
    void updateTimer();

private:
    QTimer timer;
    int elapsedTime;
    int lap_time;
    int summ_time;
    QList<int> lapStartTimes;
    int time_last_lap;
    bool running;
};

#endif // STOPWATCH_H
