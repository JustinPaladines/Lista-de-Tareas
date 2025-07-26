#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream> //ifstream/ofstream (cargar/guardar archivo)
#include <QMessageBox> //mostrar mensajes flotantes de error o éxito,
#include <vector> //contenedor dinamico
#include <string> //trabajar con cadenas de texto
#include <QFile> //para trabajar con archivos en Qt (guardar y leer)
#include <QTextStream> //leer/escribir texto en archivos con QFile
#include <QString> //trabajar con texto en Qt
#include <QComboBox> //widget desplegable con opciones

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBoxEstadoActualizar->addItems({"pendiente", "completada"});
    ui->comboBoxEstadoActualizar->setVisible(true);
    ui->comboBoxEstadoActualizar->setEnabled(true);
    ui->comboBoxEstadoActualizar->raise();

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

void MainWindow::guardar_todas_las_tareas(const QString &archivo) {
    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar.");
        return;
    }

    QTextStream out(&file);
    for (const Tarea &t : tareas) {
        QString estadoTexto = t.estado ? "pendiente" : "completada";
        out << t.numero_tarea << "|"
            << QString::fromStdString(t.descripcion) << "|"
            << estadoTexto << "\n";
    }

    file.close();
}

void MainWindow::renumerarTareas() {
    for (size_t i = 0; i < tareas.size(); ++i) {
        tareas[i].numero_tarea = i + 1; // asigna números consecutivos empezando desde 1
    }
    guardar_todas_las_tareas("cronilist.txt"); // guarda el nuevo orden en el archivo
}

void MainWindow::cargarTareasDesdeArchivo(const string& archivoTareas) {
    tareas.clear();

    ifstream archivo("cronilist.txt");
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string numero, descripcion, estado;

        getline(ss, numero, '|');
        getline(ss, descripcion, '|');
        getline(ss, estado);

        Tarea t;
        t.numero_tarea = stoi(numero);
        t.descripcion = descripcion;
        t.estado = (estado == "pendiente");

        tareas.push_back(t);
    }
}

void MainWindow::guardar_tarea(const Tarea &tarea, const QString &archivo) {
    QFile file(archivo);
    if (!file.open(QIODevice::Append | QIODevice::Text)) { //abrimos el archivo en modo añadir
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar."); //mensaje de error por si no se puede abrir el archivo
        return;
    }
    QTextStream out(&file); //escribir dentro del archivo
    QString estadoTexto = tarea.estado ? "pendiente" : "completada"; //pasamos los 1 y 0 ha texto
    out << tarea.numero_tarea << "|" << QString::fromStdString(tarea.descripcion) << "|" << estadoTexto << "\n";
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
    Tarea nueva;
    nueva.descripcion = descripcion.toStdString();
    nueva.estado = true;
    nueva.numero_tarea = contar_tareas("cronilist.txt") + 1;

    guardar_tarea(nueva, "cronilist.txt");

    ui->labelEstado->setText("Tu tarea ha sido agregada. ¡No olvides realizarla! :)");
    ui->lineEditDescripcion->clear(); // se borra el texto para que pueda ingresar una nueva tarea
}

void MainWindow::mostrarTareas()
{
    cargarTareasDesdeArchivo("cronilist.txt");
    ui->txtTareas->clear();

    if (tareas.empty()) {
        ui->txtTareas->setText("No hay tareas registradas.");
    } else {
        QString texto;
        for (const auto &tarea : tareas) {
            texto += QString::number(tarea.numero_tarea) +
                     ".- "+ QString::fromStdString(tarea.descripcion) +
                     " | Estado: " + (tarea.estado ? "pendiente" : "completada") + "\n";
        }
        ui->txtTareas->setText(texto);
    }
}

void MainWindow::actualizar_tarea() {
    bool ok;
    int numero = ui->lineEditActualizar->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Número de tarea inválido.");
        return;
    }

    auto it = std::find_if(tareas.begin(), tareas.end(), [numero](const Tarea& t) {
        return t.numero_tarea == numero;
    });
    if (it == tareas.end()) {
        QMessageBox::warning(this, "Error", "No se encontró la tarea con ese número.");
        return;
    }

    QString nuevaDescripcion = ui->lineEditDescripcionActualizar->text().trimmed();
    if (!nuevaDescripcion.isEmpty()) {
        it->descripcion = nuevaDescripcion.toStdString();
    }
    QString estadoSeleccionado = ui->comboBoxEstadoActualizar->currentText();
    it->estado = (estadoSeleccionado.toLower() == "pendiente");

    guardar_todas_las_tareas("cronilist.txt");

    QMessageBox::information(this, "Éxito", "Tarea actualizada correctamente.");
    ui->lineEditActualizar->clear();
    ui ->lineEditDescripcionActualizar->clear();
}

void MainWindow::on_actualizarButton_clicked() {
    actualizar_tarea();
}

//se quitó el void_btnMostrar porque ya la estamos conectando con la funcion de arriba
//faltan funciones para complementar, pero son base

void MainWindow::on_btnEliminarTarea_clicked() {
    cargarTareasDesdeArchivo("cronilist.txt");
    int numero = ui->txtNumeroEliminar->text().toInt();
    //creo la variable numero como entero
    //y mediante el puntero, hago que acceda al objeto texto de la interfaz
    auto it = std::find_if(tareas.begin(), tareas.end(), [numero](const Tarea& tareas) {
        return tareas.numero_tarea == numero;
    });
    if (it != tareas.end()) {
        tareas.erase(it);
        renumerarTareas();
        guardar_todas_las_tareas("cronilist.txt");
        QMessageBox::information(this, "Éxito", "Tarea eliminada correctamente");
    } else {
        QMessageBox::warning(this, "Error", "No se encontró la tarea con ese número");
    }
    ui->txtNumeroEliminar->clear();
}
