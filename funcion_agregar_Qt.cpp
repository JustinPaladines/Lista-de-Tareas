#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFile>          // Para manejar archivos
#include <QTextStream>    // Para escribir/leer texto
#include <QMessageBox>    // Para mostrar mensajes de error
#include <QDebug>         //Opcional para imprimir en consola

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //se conecta el boton con la funcion agregar tarea
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
    QString estadoTexto = tarea.estado ? "pendiente" : "completa"; //pasamos los 1 y 0 ha texto
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
