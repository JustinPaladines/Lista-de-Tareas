void actualizar_tarea(vector<tarea>& tareas) {
    int numero;
    bool encontrado = false;
    cout<<"Ingrese el numero de la tarea: \n";
    cin>>numero;
    for (int i = 0; i<tareas.size(); i++) {
        cout<<"Buscando...";

        if  (tareas[i].numero_tarea == numero) {
            cout<< "Se quiere actualizar la tarea: \n"<<tareas[i].tarea<<endl;
            cout<<"Ingrese el nuevo nombre para la tarea: \n";
            cin.ignore();
            getline(cin, tareas[i].tarea);
            cout<<"Se ha actualizado con exito"
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout<<"No se encontro la tarea";
    }
}