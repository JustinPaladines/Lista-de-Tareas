#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include <vector>
#include <string>
#include <QString>
#include <QComboBox>
using namespace std;

struct Tarea {
    int numero_tarea;
    string descripcion;
    bool estado; // true = Pendiente, false = Completada
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
    void guardar_todas_las_tareas(const QString &archivo);
    void cargarTareasDesdeArchivo(const string& archivoTareas);
    
private slots:
    void on_btnEliminarTarea_clicked();

};
#endif // MAINWINDOW_H

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
