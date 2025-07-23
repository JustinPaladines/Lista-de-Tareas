void actualizar_tarea(vector<tarea>& tareas) {
    int numero;
    bool encontrado = false;
    cout<<"Ingrese el numero de la tarea: \n";
    cin>>numero;
    for (int i = 0; i<tareas.size(); i++) {

        if  (tareas[i].numero_tarea == numero) {
            cout<< "Se quiere actualizar la tarea: \n"<<tareas[i].descripcion<<endl;
            cout<<"Ingrese el nuevo nombre para la tarea: \n";
            cin.ignore();
            getline(cin, tareas[i].descripcion);
            cout<<"Se ha actualizado con exito\n";
            int nuevo_estado;
            cout<<"¿La tarea esta completada? (SI : 1 - NO: 0\n)";
            cin>>nuevo_estado;
            tareas[i].estado = (nuevo_estado==1);
            cout<<"Se ha actualizado con exito\n";
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout<<"No se encontro la tarea";
    }
}
//ARCHIVOSSS
void guardar_tareas_actualizadas(const vector<tarea>& tareas, const string& cronilist){
    ofstream archivo("cronilist.txt");
    if (!archivo.is_open()){
        cerr<<"ERROR AL GUARDAR\n";
        return;
    }
    for (const auto& tarea : tareas){
        string estadoTarea = tarea.estado ? "pendiente" : "completo";
        archivo << tarea.numero_tarea << " | " << tarea.descripcion << " | " << estado_tarea << endl;
    }
    archivo.close();
}

