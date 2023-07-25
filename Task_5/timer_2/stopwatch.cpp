#include "stopwatch.h"
#include <QDebug>


Stopwatch::Stopwatch(QObject *parent) : QObject(parent), elapsedTime(0), running(false),  lap_time (0), summ_time(0) {
    connect(&timer, &QTimer::timeout, this, &Stopwatch::updateTimer);
}

void Stopwatch::start() {
    if (!running) {
        running = true;
        lapStartTimes.append(QDateTime::currentMSecsSinceEpoch());
        timer.start(100);
    }
}

void Stopwatch::stop() {
    if (running) {
        lap_time = 0;
        summ_time = 0;
        running = false;
        elapsedTime += QDateTime::currentMSecsSinceEpoch() - lapStartTimes.last();
        timer.stop();
    }
}

void Stopwatch::reset() {
    lap_time = 0;
    summ_time = 0;
    elapsedTime = 0;
    lapStartTimes.clear();
    running = false;
    timer.stop();
    emit timeUpdated(elapsedTime);
}

bool Stopwatch::isRunning() const {
    return running;
}

int Stopwatch::getTime() const {
    return running ? (elapsedTime + QDateTime::currentMSecsSinceEpoch() - lapStartTimes.last()) : elapsedTime;
}

int Stopwatch::getLapTime(){
    int time = getTime();
    lap_time = time - summ_time;
    summ_time = time;
    qDebug() << "time = " << time;
    qDebug() << "summ_time = " << summ_time;
    qDebug() << "lap_time = " << lap_time;

    return lap_time;
}

void Stopwatch::updateTimer() {
    emit timeUpdated(getTime());
}
