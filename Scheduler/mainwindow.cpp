#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graph.h"
#include "schedule.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList lst;
    lst << "Источник" << "Цель";
    ui->edgesInputTable->setHorizontalHeaderLabels(lst);
    edgesCount = 0;
    vertexCount = 0;
    processorCount.fill(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphInputBtn_clicked()
{
    //Формирование графа из введённых в таблицу данных
    Graph G(vertexCount);
    Edge newEdge;
    for ( int i = 0; i < edgesCount; i++ ){
        newEdge.source = ui->edgesInputTable->item(i, 0)->text().toInt();
        newEdge.destination = ui->edgesInputTable->item(i, 1)->text().toInt();
        //Граф невзвешеный
        newEdge.weight = 1;
        G.InsertEdge(newEdge);
    }
    for ( int processorType = 0; processorType < taskTypeCount; processorType++){
        processorCount[processorType] = ui->processorCountTable->item(0, processorType)->text().toInt();
    }
    for ( int task = 0; task < vertexCount; task++ ){
        taskType[task] = ui->taskTypeTable->item(task, 0)->text().toInt();
    }

    //Формирование расписания
    Schedule schedule(G, processorCount, taskType);
    QVector< QVector<int> > taskSequence = schedule.formSchedule();

    //Вывод расписания
    QString outputString = "Последовательность выполнения : \n";
    QString num = "";
    for ( int time = 0; time < taskSequence.size(); time++){
        for ( int task = 0; task < taskSequence[time].size(); task++ ){
            num.setNum( taskSequence[time][task] );
            num += ' ';
            outputString += num;
        }
        outputString += '\n';
    }
    ui->plainTextEdit->setPlainText(outputString);
}

void MainWindow::on_vertexCountEdit_editingFinished()
{
    vertexCount = ui->vertexCountEdit->text().toInt();
    ui->taskTypeTable->setRowCount(vertexCount);
    QStringList lst;
    QString title;
    for ( int i=0; i < vertexCount; i++){
        title.setNum(i);
        lst << title;
    }
    ui->taskTypeTable->setVerticalHeaderLabels(lst);
    ui->taskTypeTable->setHorizontalHeaderLabels(QStringList("Тип процесса"));

}

void MainWindow::on_edgesCountEdit_editingFinished()
{
    edgesCount = ui->edgesCountEdit->text().toInt();
    taskType.fill(0,edgesCount);
    ui->edgesInputTable->setRowCount(edgesCount);

}



void MainWindow::on_typeCountEdit_editingFinished()
{
     taskTypeCount = ui->typeCountEdit->text().toInt();
     processorCount.fill(0, taskTypeCount);
     ui->processorCountTable->setColumnCount(taskTypeCount);
     QStringList lst;
     QString title;
     for ( int i=0; i < taskTypeCount; i++){
         title.setNum(i);
         title += "-й тип";
         lst << title;
     }
     ui->processorCountTable->setHorizontalHeaderLabels(lst);
     ui->processorCountTable->setVerticalHeaderLabels(QStringList("Количество"));

}
