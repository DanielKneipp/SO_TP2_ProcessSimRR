#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), n_iter(0), quantum(0)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Pronto.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->n_iter = ui->spinBox_n_iter->value();
    this->quantum = ui->spinBox_quantum->value();

    ui->statusBar->showMessage("Executando...");
    this->info = simular_RoundRobin(n_iter, quantum);
    ui->statusBar->showMessage("Pronto.");

    ui->label_TrTx->setText (QString::number(info.TrTx_media));
    ui->label_n_proc_exec->setText (QString::number(info.n_processos_executados));
    ui->label_temp->setText (QString::number(info.tempo_corrido) + "ms");
}
