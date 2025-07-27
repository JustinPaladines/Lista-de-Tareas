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
    QString descripcion;
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
    int contar_tareas(const QString &archivo);
    void guardar_tarea(const Tarea &tarea, const QString &archivo);
    void cargar_tareas_desde_archivo(const QString& archivo, QVector<Tarea>& tareas);
    void mostrarTareas();
    void agregar_tarea();
    void guardar_todas_las_tareas(const QString &archivo);
    void cargarTareasDesdeArchivo(const string& archivoTareas);
    void renumerarTareas();
    void actualizar_tarea();

private slots:
    //void on_btnMostrarTareas_clicked();
    void on_btnEliminarTarea_clicked();
    void on_actualizarButton_clicked();

};
#endif // MAINWINDOW_H
