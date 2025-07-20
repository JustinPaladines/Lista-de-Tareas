#include<iostream>
#include<fstream>
#include<string>
#include <vector>
using namespace std;


struct tarea{
	
	int numero_tarea;
	string descripcion;
	bool estado;
};

vector<tarea>tareas = {}; 

// funcion que cuenta cuantas tareas existen para asi desde ahi seguir contando  
int contar_tareas(const string& cronilist) {
	
	ifstream archivo(cronilist); 
	int contador = 0;
	string linea;
	while (getline(archivo, linea)) { 
		if (!linea.empty()) contador++; //si las lineas no estan vacias se incrementa
	}
	archivo.close();
	return contador;
}

//no sobreescribira la tarea, si no la colocara al final de la anterior 
void guardar_tarea(const tarea& nueva_tarea, const string& cronilist) {
	
	ofstream archivo(cronilist, ios::app);
	if (!archivo.is_open()) {
		cerr << "Error al guardar en archivo." << endl;
		return;
	}
	string estado_tarea = nueva_tarea.estado ? "pendiente" : "completa"; //cambiamos el estado a texto 
	archivo << nueva_tarea.numero_tarea << " | " << nueva_tarea.descripcion << " | " << estado_tarea << endl;
	archivo.close();
	
}

void agregar_tarea(vector<tarea>& tareas){
	
	tarea nueva_tarea;
	// contar cuantas tareas hay en el archivo y continuar desde ahí
	int existentes = contar_tareas("cronilist.txt");
	nueva_tarea.numero_tarea = existentes + 1;
	cout<<"Ingrese su nueva tarea aqui: "<<endl;
	getline(cin, nueva_tarea.descripcion);
	cin.ignore();
	nueva_tarea.estado = true;
	
	tareas.push_back(nueva_tarea); //se añade la tarea al vector 
	cout << "Su tarea ha sido agregada. ¡No olvides realizarla!" << endl;
	
	guardar_tarea(nueva_tarea, "cronilist.txt");
		
}
	
int main() {
		
	setlocale(LC_ALL, "spanish");
	agregar_tarea(tareas);
	
	return 0;
		
}
