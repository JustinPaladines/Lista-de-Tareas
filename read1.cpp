#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<locale>
using namespace std;

struct Tarea{
	int numero_tarea;
	string tarea;
	bool estado;
};

vector<Tarea>tareas = {}; 

void verTareas (const vector<Tarea>& tareas){
	cout<<"\n-----Lista de tareas----\n";
	if (tareas.empty()){
		cout<<"No hay tareas registradas"<<endl;
	}else{
		for(const auto &tarea: tareas){
			cout<<"Número de tarea: "<<tarea.numero_tarea<<"- Desecripción: "<<tarea.tarea
			<< " - Estado: " << (tarea.estado ? "Completada" : "Pendiente") << endl;	
		}
	}
}

int main() {
	setlocale(LC_ALL,"");
    vector<Tarea> tareas = {
        {1, "prueba para ver si vale", false},
        {2, "hacer tarea de programación", true}
    };

    verTareas(tareas);
    return 0;
}
