/*Se borró la función que habia agregada debido a que mis compañeroñeros
 ya la habian hecho y ddecidimos optar x ella, y finalemente cambie mi función
 que contaba con gráficos emergentes ya que no iba adeacuado a los compañeros*/

//Para comboBox(estado de las tareas)
ui->comboBoxEstadoActualizar->addItems({"Pendiente", "Completada"});
ui->comboBoxEstadoActualizar->setVisible(true);
ui->comboBoxEstadoActualizar->setEnabled(true);
ui->comboBoxEstadoActualizar->raise();


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


void MainWindow::guardar_tareas_actualizadas(const QString& archivo) {
 QFile file(archivo);
 if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
  QMessageBox::critical(this, "Error", "No se pudo abrir el archivo para guardar.");
  return;
