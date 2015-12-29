#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_graphInputBtn_clicked();

    void on_vertexCountEdit_editingFinished();

    void on_edgesCountEdit_editingFinished();

    void on_typeCountEdit_editingFinished();

private:
    int edgesCount;
    int vertexCount;
    QVector<int> processorCount;
    QVector<int> taskType;
    int taskTypeCount;
    Ui::MainWindow *ui;
\
};

#endif // MAINWINDOW_H
