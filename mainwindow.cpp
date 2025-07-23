#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectar botón a la función para mostrar tareas
    connect(ui->btnMostrarTareas, &QPushButton::clicked, this, &MainWindow::mostrarTareas);

    // Tareas de ejemplo (puedes eliminarlas)
    tareas.push_back({1, "prueba para ver ", false});
    tareas.push_back({2, "estudiar para el examen de programacion", true});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mostrarTareas()
{
    ui->txtTareas->clear();

    if (tareas.empty()) {
        ui->txtTareas->setText("No hay tareas registradas.");
    } else {
        QString texto;
        for (const auto &tarea : tareas) {
            texto += "Número de tarea: " + QString::number(tarea.numeroTarea) +
                     " - Descripción: " + QString::fromStdString(tarea.descripcion) +
                     " - Estado: " + (tarea.estado ? "Completada" : "Pendiente") + "\n";
        }
        ui->txtTareas->setText(texto);
    }
}
void MainWindow::on_btnMostrarTareas_clicked()
{
    mostrarTareas();  // Aquí llamas a tu función real
}



void MainWindow::on_txtTareas_copyAvailable(bool b)
{

}

