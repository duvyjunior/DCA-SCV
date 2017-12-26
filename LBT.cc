#include <iostream>
#include <string>
#include <ctime>
#include "stdio.h"
#include "time.h"
#include <vector>
#include "stdlib.h"
//@autor David Pérez Segura
using namespace std;
struct Respuesta {
	string quien;
	int respID;
	string message;
	string autor;
	string fecha;
}
;
struct Error {
	string quien;
	int errorID;
	string message;
	string autor;
	bool estado;
	// 0 -> Cerrado, 1 -> Abierto
	int gravedad;
	string fecha;
	vector <Respuesta> respuestas;
}
;
struct Project {
	int id;
	string title;
	string description;
	string autor;
	vector <Error> errores;
	string fecha;
}
;
vector <Project> proyectos;
string quienEs;
string fecha() {
	time_t   t,i;
	char *p;
	i = time (&t);
	p = ctime (&i);
	return p;
}
void tomarDatosProyecto();
void tomarDatosError(int id);
void mostrarProyectos();
void mostrarIncidencias(int id);
void tomarDatosRespuesta(int id, int num);
void mostrarIncidencia(int id, int num);
int main() {
	string quien;
	cout<<"Bienvenido a LBT"<<endl;
	do {
		cout<<"¿Eres desarrollador o usuario?"<<endl;
		cin>>quien;
		if(quien == "desarrollador" || quien == "Desarrollador") {
			quienEs = "desarrollador";
			int opt=0;
			string resp, resp2;
			system("clear");
			do {
				cout<<"Bienvenido desarrollador"<<endl;
				cout << "Introduce qué quieres hacer" << endl;
				cout << "1- Introducir un nuevo proyecto" << endl;
				cout << "2- Elegir un proyecto ya existente" << endl;
				cout << "3- Salir" << endl;
				cin>>opt;
				switch(opt) {
					case 1:
					             tomarDatosProyecto();
					main();
					break;
					case 2:
					if(proyectos.size() > 0){
					        int id;
						mostrarProyectos();
						cin>>id;
						system("clear");
						mostrarIncidencias(id);
						if(proyectos.size() > 0) {
							do {
								cout<<"¿Deseas añadir una nueva incidencia?"<<endl;
								cin>>resp;
								if(resp == "si" || resp == "Si") {
									tomarDatosError(id);
									main();
								} else if(resp == "no" || resp == "No") {
									do {
										cout<<"¿Desea responder alguna incidencia?"<<endl;
										cin>>resp2;
										if(resp2 == "si" || resp2 == "Si") {
											int num;
											cout<<"Introduce su numero de ID"<<endl;
											cin>>num;
											system("clear");
											mostrarIncidencia(id, num-1);
											tomarDatosRespuesta(id, num);
											main();
										} else if(resp2 == "no" || resp2 == "No") {
											main();
										} else {
											cout<<"No te he entendido, prueba otra vez"<<endl;
										}
									}
									while(resp2 != "si" && resp2 != "Si" && resp2 != "no" && resp2 != "No");
								} else {
									cout<<"No te he entendido, prueba otra vez"<<endl;
								}
							}
							while(resp != "si" && resp != "Si" && resp != "no" && resp != "No");
						}
					}
					else{
						system("clear");
						cout<<"No hay proyectos disponibles aún"<<endl;
						main();
					}
					break;
					case 3:
					             cout<<"Hasta pronto!"<<endl;
					break;
					default:
					             cout<<"Por favor, introduce una opción válida"<<endl<<endl;
					break;
				}
			}
			while(opt < 1 || opt > 3);
		} else if(quien == "usuario" || quien == "Usuario") {
			quienEs = "usuario";
			int opt=0;
			string resp, resp2;
			system("clear");
			do {
				cout<<"Bienvenido usuario"<<endl;
				cout << "Introduce qué quieres hacer" << endl;
				cout << "1- Elegir un proyecto ya existente" << endl;
				cout << "2- Salir" << endl;
				cin>>opt;
				switch(opt) {
					case 1:
					if(proyectos.size() >0){
						int id;
						mostrarProyectos();
						cin>>id;
						system("clear");
						mostrarIncidencias(id);
						if(proyectos.size() > 0) {
							do {
								cout<<"¿Deseas añadir una nueva incidencia?"<<endl;
								cin>>resp;
								if(resp == "si" || resp == "Si") {
									tomarDatosError(id);
									main();
								} else if(resp == "no" || resp == "No") {
									do {
										cout<<"¿Desea responder alguna incidencia?"<<endl;
										cin>>resp2;
										if(resp2 == "si" || resp2 == "Si") {
											int num;
											cout<<"Introduce su numero de ID"<<endl;
											cin>>num;
											system("clear");
											mostrarIncidencia(id, num-1);
											tomarDatosRespuesta(id, num);
											main();
										} else if(resp2 == "no" || resp2 == "No") {
											main();
										} else {
											cout<<"No te he entendido, prueba otra vez"<<endl;
										}
									}
									while(resp2 != "si" && resp2 != "Si" && resp2 != "no" && resp2 != "No");
								} else {
									cout<<"No te he entendido, prueba otra vez"<<endl;
								}
							}
							while(resp != "si" && resp != "Si" && resp != "no" && resp != "No");
						}
					}
					else{
						system("clear");
						cout<<"No hay proyectos disponibles aún"<<endl;
						main();
					}
					break;
					case 2:
					      			 cout<<"Hasta pronto!"<<endl;
					break;
					default:
					      			 cout<<"Por favor, introduce una opción válida"<<endl<<endl;
					break;
				}
			}
			while(opt < 1 || opt > 3);
		} else {
			cout<<"Lo siento, no te he entendido, vuelve a probar"<<endl;
		}
	}
	while(quien != "usuario" && quien != "Usuario" && quien != "desarrollador" && quien != "Desarrollado");
	return 0;
}
void tomarDatosProyecto() {
	Project proyecto;
	string t, d, nombre;
	proyecto.id = proyectos.size()+1;
	proyecto.fecha = fecha();
	cin.ignore();
	cout<<"Introduce el título del proyecto"<<endl;
	getline(cin, t);
	proyecto.title = t;
	cout<<"Introduce una descripción del proyecto"<<endl;
	getline(cin, d);
	proyecto.description = d;
	cout << "Introduce el nombre del autor del proyecto" <<endl;
	getline(cin, nombre);
	proyecto.autor = nombre;
	proyectos.push_back(proyecto);
	cout<<"Tamaño: "<<proyectos.size()<<endl;
	system("clear");
	cout<<"Guardado con exito!"<<endl;
}
void tomarDatosError(int id) {
	string nombre, mensaje;
	int gravedad;
	Error error;
	error.estado = 1;
	error.fecha = fecha();
	error.errorID = proyectos[id-1].errores.size() +1;
	cin.ignore();
	cout<<"Introduce tu nombre"<<endl;
	getline(cin, nombre);
	error.autor = nombre;
	cout<<"Introduce la gravedad de la incidencia del 1 al 10"<<endl;
	cin>>gravedad;
	error.gravedad = gravedad;
	cin.ignore();
	cout<<"Introduce cómo ha sucedido la incidencia y de qué se trata"<<endl;
	getline(cin, mensaje);
	error.message = mensaje;
	error.quien = quienEs;
	proyectos[id-1].errores.push_back(error);
	system("clear");
	cout<<"Incidencia guardada con exito!"<<endl;
}
void tomarDatosRespuesta(int id, int num) {
	Respuesta resp;
	string nombre, respuesta;
	resp.respID = proyectos[id-1].errores[num-1].respuestas.size() +1;
	resp.fecha = fecha();
	cin.ignore();
	cout<<"Introduce tu nombre"<<endl;
	getline(cin, nombre);
	resp.autor = nombre;
	cout<<"Introduce tu respuesta"<<endl;
	getline(cin, respuesta);
	resp.message = respuesta;
	resp.quien = quienEs;
	proyectos[id-1].errores[num-1].respuestas.push_back(resp);
}
void mostrarProyectos() {
	system("clear");
	cout<<"Introduce el ID de un proyecto para acceder a el"<<endl;
	for (int i=0; i< proyectos.size(); i++) {
		cout << "\033[1;36m";
		cout<<"ID: " << proyectos[i].id<<endl;
		cout<<"Autor: "<<proyectos[i].autor<<endl;
		cout<<"Fecha: "<<proyectos[i].fecha;
		cout<<"Titulo: "<<proyectos[i].title<<endl;
		cout<<"Descripción: "<<proyectos[i].description<<endl;
		cout << "\033[0m\n";
		mostrarIncidencias(i+1);
		cout<<endl;
	}
}
void mostrarIncidencias(int id) {
	if(proyectos[id -1].errores.size() > 0) {
	cout<<"----- Estas son las incidencias del proyecto "<<id<<" -----"<<endl;
		for (int i=0; i<proyectos[id-1].errores.size(); i++) {
			mostrarIncidencia(id, i);
			cout<<"----------------------------------------------------"<<endl;
		}
	} else {
		cout<<"No hay incidencias aún"<<endl;
	}
}
void mostrarRespuestas(int id, int num) {
	if(proyectos[id-1].errores[num].respuestas.size() >0) {
		cout<<"*******************RESPUESTAS***************"<<endl;
		for (int i=0; i<proyectos[id-1].errores[num].respuestas.size(); i++) {
			if(proyectos[id-1].errores[num].respuestas[i].quien == "usuario") {
					cout << "\033[1;32m";
			} else if(proyectos[id-1].errores[num].respuestas[i].quien == "desarrollador") {
				cout << "\033[1;31m";
			}
			cout<<"Autor: "<<proyectos[id-1].errores[num].respuestas[i].autor<<endl;
			cout<<"Fecha: "<<proyectos[id-1].errores[num].respuestas[i].fecha;
			cout<<"Respuesta: "<<proyectos[id-1].errores[num].respuestas[i].message<<endl;
			cout << "\033[0m\n";
		}
		cout<<"*******************************************"<<endl;
	} else {
	}
}
void mostrarIncidencia(int id, int num) {
	if(proyectos[id-1].errores[num].quien == "usuario") {
		cout << "\033[1;34m";
	} else if(proyectos[id-1].errores[num].quien == "desarrollador") {
		cout << "\033[1;34m";
	}
	cout<<"ID: "<<proyectos[id-1].errores[num].errorID<<endl;
	cout<<"Desarrollador o usuario: "<<proyectos[id-1].errores[num].quien<<endl;
	cout<<"Autor: "<<proyectos[id-1].errores[num].autor<<endl;
	cout<<"Fecha: "<<proyectos[id-1].errores[num].fecha;
	cout<<"Gravedad: "<<proyectos[id-1].errores[num].gravedad<<endl;
	cout<<"Mensaje: "<<proyectos[id-1].errores[num].message<<endl;
	cout << "\033[0m\n";
	mostrarRespuestas(id, num);
}
