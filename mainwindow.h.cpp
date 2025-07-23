#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>

struct tarea {
    int numero_tarea;
    QString descripcion;
    bool estado; // true = pendiente, false = completa
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actualizarButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<tarea> tareas;

    void actualizar_tarea();
    void guardar_tareas_actualizadas(const QString& archivo);
};

#endif // MAINWINDOW_H
