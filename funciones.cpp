//MAINWINDOW.H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <vector>
#include <string>

using namespace std;

struct Tarea {
    int numero_tarea;
    string descripcion;
    bool estado; // false = Pendiente, true = Completada
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    vector<Tarea> tareas;
    int contar_tareas(const QString &archivo);
    void guardar_tarea(const tarea &tarea, const QString &archivo);
    void mostrarTareas();
    void agregar_tarea();

private slots:
    void on_btnMostrarTareas_clicked();
};
#endif // MAINWINDOW_H


/// MAINWINDOW.CPP

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnMostrarTareas, &QPushButton::clicked, this, &MainWindow::mostrarTareas);
    connect(ui->btnAgregar, &QPushButton::clicked, this, &MainWindow::agregar_tarea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::contar_tareas(const QString &archivo) {
    QFile file(archivo); //se crea un objeto para poder trabajar con el archivo
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //abrimos el archivo en modo lectura
        return 0;

    int contador = 0; //ponemos un contador para saber cuantas tareas hay
    QTextStream in(&file); //para leer el archivo linea por linea
    while (!in.atEnd()) { //mientras no se llegue all final del archivo
        QString linea = in.readLine(); //lee una linea
        if (!linea.trimmed().isEmpty()) //quita espacios al inicio y final y verifica si la linea no esta vacia
            contador++;
    }
    file.close();
    return contador; //se cierra el archivo y se regresa el numero de tareas
}

void MainWindow::guardar_tarea(const tarea &tarea, const QString &archivo) {
    QFile file(archivo);
    if (!file.open(QIODevice::Append | QIODevice::Text)) { //abrimos el archivo en modo añadir
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar."); //mensaje de error por si no se puede abrir el archivo
        return;
    }

    QTextStream out(&file); //escribir dentro del archivo
    QString estadoTexto = tarea.estado ? "pendiente" : "completada"; //pasamos los 1 y 0 ha texto
    out << tarea.numero_tarea << " | " << tarea.descripcion << " | " << estadoTexto << "\n";
    file.close();
}

void MainWindow::agregar_tarea() {

    QString descripcion = ui->lineEditDescripcion->text().trimmed();

    //si esta vacio el lugar donde el usuario coloca la tarea y trata de subirla mostrara un mensaje de error
    if (descripcion.isEmpty()) {
        ui->labelEstado->setText("Por favor, escribe tu tarea.");
        return;
    }

    //se crea la tarea
    tarea nueva;
    nueva.descripcion = descripcion;
    nueva.estado = true;
    nueva.numero_tarea = contar_tareas("cronilist.txt") + 1;

    guardar_tarea(nueva, "cronilist.txt");

    ui->labelEstado->setText("Tu tarea ha sido agregada. ¡No olvides realizarla! :)");
    ui->lineEditDescripcion->clear(); // se borra el texto para que pueda ingresar una nueva tarea
}

void MainWindow::mostrarTareas()
{
    ui->txtTareas->clear();

    if (tareas.empty()) {
        ui->txtTareas->setText("No hay tareas registradas.");
    } else {
        QString texto;
        for (const auto &tarea : tareas) {
            texto += "Número de tarea: " + QString::number(tarea.numero_tarea) +
                     " - Descripción: " + QString::fromStdString(tarea.descripcion) +
                     " - Estado: " + (tarea.estado ? "pendiente" : "completada") + "\n";
        }
        ui->txtTareas->setText(texto);
    }
}

//se quitó el void_btnMostrar porque ya la estamos conectando con la funcion de arriba
//faltan funciones para complementar, pero son base

