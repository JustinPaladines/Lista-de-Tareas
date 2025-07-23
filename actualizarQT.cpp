#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

void cargar_tareas_desde_archivo(const QString& archivo, QVector<tarea>& tareas) {
    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    tareas.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QStringList partes = in.readLine().trimmed().split('|');
        if (partes.size() != 3) continue;

        bool ok;
        int numero = partes[0].trimmed().toInt(&ok);
        if (!ok) continue;

        tareas.append({numero, partes[1].trimmed(), partes[2].trimmed().toLower() == "pendiente"});
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    cargar_tareas_desde_archivo("cronilist.txt", tareas);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::actualizar_tarea() {
    bool ok;
    int numero = QInputDialog::getInt(this, "Actualizar Tarea", "Número de la tarea:", 1, 1, 10000, 1, &ok);
    if (!ok) return;

    for (auto &t : tareas) {
        if (t.numero_tarea == numero) {
            QString descNueva = QInputDialog::getText(this, "Actualizar Tarea",
                                                      "Tarea actual:\n" + t.descripcion + "\nNueva descripción:", QLineEdit::Normal, t.descripcion, &ok);
            if (!ok) return;
            t.descripcion = descNueva;

            int estado = QMessageBox::question(this, "Estado de la tarea", "¿Está completada?", QMessageBox::Yes | QMessageBox::No);
            t.estado = (estado == QMessageBox::No);

            QMessageBox::information(this, "Éxito", "Tarea actualizada con éxito.");
            guardar_tareas_actualizadas("cronilist.txt");
            return;
        }
    }
    QMessageBox::warning(this, "No encontrado", "No se encontró la tarea con ese número.");
}

void MainWindow::guardar_tareas_actualizadas(const QString& archivo) {
    QFile file(archivo);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo para guardar.");
        return;
    }

    QTextStream out(&file);
    for (const auto& t : tareas)
        out << t.numero_tarea << " | " << t.descripcion << " | " << (t.estado ? "pendiente" : "completa") << "\n";
}

void MainWindow::on_actualizarButton_clicked() {
    actualizar_tarea();
}
