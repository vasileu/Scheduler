#include "schedule.h"
#include "QQueue"


#define COMPLETED_TASK -1

Schedule::Schedule(const Graph &graph, const QVector<int> &processorCount, const QVector<int> &taskType) :
    graph(graph),
    processorCount(processorCount),
    taskType(taskType)
{

}


void Schedule::initSchedule()
{
    waitingTaskCount.fill(0, graph.VertexCount());
    for ( int vertexNumber = 0; vertexNumber < graph.VertexCount(); vertexNumber++ ){
        EdgesIterator outEdge(graph, vertexNumber);
        for ( Edge edge = outEdge.begin(); !outEdge.end(); edge = outEdge.nextItem() ){
            waitingTaskCount[edge.destination]++;
        }
    }
}

QVector< QVector<int> > Schedule::formSchedule()
{
    initSchedule();
    for (int i = 0; i < processorCount.size(); i++){
        if (processorCount[i] <= 0){
            taskSequence.push_back(QVector<int>(1,-1));
            return taskSequence;
        }
    }
    QVector<int> tasksToDoOnThisTime;
    QVector<int> tasksPerProcCount(processorCount.size(), 0);
    bool complete = false;
    while( !complete ){
        complete = true;
        tasksPerProcCount.fill(0);
        for (int taskNumber = 0; taskNumber < waitingTaskCount.size(); taskNumber++ ){
            if (waitingTaskCount[taskNumber] != COMPLETED_TASK){
                complete = false;
            }

            if (waitingTaskCount[taskNumber] == 0){
                int processorType = taskType[taskNumber];
                if ( (tasksPerProcCount[processorType] < processorCount[processorType])){
                    tasksToDoOnThisTime.push_back(taskNumber);
                    tasksPerProcCount[processorType]++;
                }
            }
        }

        for ( int task = 0; task < tasksToDoOnThisTime.count(); task++ ){
            int taskToDo = tasksToDoOnThisTime[task];
            EdgesIterator neighbour(graph, taskToDo);
            for ( Edge edge = neighbour.begin(); !neighbour.end(); edge = neighbour.nextItem() ){
                 waitingTaskCount[edge.destination]--;
            }
            waitingTaskCount[taskToDo] = COMPLETED_TASK;
        }
        taskSequence.push_back(tasksToDoOnThisTime);
        tasksToDoOnThisTime.resize(0);
    }
    return taskSequence;
}
