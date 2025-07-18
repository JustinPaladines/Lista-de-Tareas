#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct Tarea{
	int numeroTarea;
	string descripcion;
	bool estado;
};

void verTareas (const vector<Tarea>& tareas){
	cout<<"\n-----Lista de tareas----\n";
	if (tareas.empty()){
		cout<<"No hay tareas registradas"<<endl;
	}else{
		for(const auto &tarea: tareas){
			cout<<"N�mero de tarea"<<tarea.numeroTarea<<"- Desecripci�n: "<<tarea.descripcion
			<< " - Estado: " << (tarea.estado ? "Completada" : "Pendiente") << endl;	
		}
	}
}
