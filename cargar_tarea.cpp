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
