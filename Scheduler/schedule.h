#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "QVector"
#include "graph.h"

class Schedule
{
    Graph graph;
    QVector< QVector<int> > taskSequence;
    QVector<int> waitingTaskCount;
    QVector<int> taskType;
    QVector<int> processorCount;
    void initSchedule();
public:
    Schedule(const Graph &graph, const QVector<int> &processorCount, const QVector<int> &taskType);
    QVector< QVector<int> > formSchedule();
};

#endif // SCHEDULE_H
