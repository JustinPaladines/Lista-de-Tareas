#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Tarea {
    int numero_tarea;
    string descripcion;
    bool estado; // false = Pendiente, true = Completada
};

vector<Tarea>tareas = {}; 

void eliminarTarea(vector<Tarea>& tareas, int numero) {
    for (auto it = tareas.begin(); it != tareas.end(); ++it) {
        if (it->numero_tarea == numero) {
            tareas.erase(it);
            cout << "Tarea eliminada correctamente.\n";
            return;
        }
    }
    cout << "No se encontró una tarea con ese número.\n";
}

//creare una funcion para guardar el archivo
//y se modifiquen los cambios al eliminar una tarea
void guardarTarea(const vector<Tarea>& tareas, const string archivoTareas){
	//uso ofstream para escribir en el archivo
	ofstream archivo(archivoTareas);
	if(!archivo.is_open()){
		cerr<<"Error! no se pudo abrir el archivo."<<endl;
		return;
		//explicado por el ingeniero, en void se puede usar return, para salir
	}
	for(const auto& tarea_cargar: tareas){
		string estado = tarea_cargar.estado ? "pendiente" : "completada";
		archivo<<tarea_cargar.numero_tarea<<"|"<<
		tarea_cargar.descripcion<<"|"<<estado<<endl;
	}
}
