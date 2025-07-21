#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Tarea {
    int numero_tarea;
    string descripcion;
    bool estado; // true = Pendiente, false = Completada
};

vector<Tarea> tareas;

void on_btnEliminarTarea_clicked();


void MainWindow::on_btnEliminarTarea_clicked() {
    int numero = ui->txtNumeroEliminar->text().toInt();
    //creo la variable numero como entero
    //y mediante el puntero, hago que acceda al objeto texto de la interfaz
    auto it = std::find_if(tareas.begin(), tareas.end(), [numero](const Tarea& tareas) {
        return tareas.numero_tarea == numero;
    });
    if (it != tareas.end()) {
        tareas.erase(it);
        guardarTarea("cronilist.txt");
        //mostrarTareasEnLista();
        QMessageBox::information(this, "Éxito", "Tarea eliminada correctamente");
    } else {
        QMessageBox::warning(this, "Error", "No se encontró la tarea con ese número");
    }
    ui->txtNumeroEliminar->clear();
}
