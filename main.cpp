#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <algorithm>
using namespace std;
#include "persona.h"
#include "lista.h"
#include "task.h"
#include "hashtablevd.h"
#include "bts.h"


void cargarLinkedLists(Hashtable<string, Persona> &h,
                         LinkedList<Persona> &personas) {
  LinkedList<string> keys = h.keysK();
  while (!keys.is_empty()) {
    string key = keys.remove_front();
    do {
      Persona p = h.get_or_default(key, Persona());
      if (p){
        personas.addLast(p);
      }
    } while (h.remove(key));
  }
}


void dCenso(Hashtable<string, Persona> &h) {
  LinkedList<Persona> personas;
  LinkedList<string> ciudades = h.keysK();
  cargarLinkedLists(h, personas);
  while (!ciudades.is_empty() && !personas.is_empty()) {
    string ciudad = ciudades.remove_front();
    int n = 0;
    cout << "-\t" << ciudad << ": ";
    while (personas.getFirst().getCity() == ciudad) {
      personas.remove_front();
      n++;
      if(personas.is_empty()) break;
    }
    cout << n << "\n";
  }
}



void ordenamientopilas(LinkedList<Persona> & desayunoConMamas){
  Stack<Persona> pilaordenada;
  Stack<Persona> data;
  Persona vartemporal;

  cout << "Complejidad O(n^2)" << endl;
  for(int i = 0; i < 50000; i++){
    data.push(desayunoConMamas.get(i));
  }
  cout << data.size() << endl;
  
  while(!data.is_empty()){
    vartemporal = data.remove_last();

    while(!pilaordenada.is_empty() && pilaordenada.peek() > vartemporal){
      data.push(pilaordenada.pop());
      
    }
    pilaordenada.push(vartemporal);
 
  }
  cout << pilaordenada.size();
  pilaordenada.print();
  
}


void menu(LinkedList<Persona> & desayunoConMamas, Hashtable<string,Persona>&personas){
  int opcion;
  do{
    cout << "Ingrsa la opción deseada: " << endl;
    cout << "1. Ver los habitantes de cada ciudad." << endl;
    cout << "2. Ver a los habitantes ordenados." << endl;
    cout << "3. Ver a los habitantes por ZIP." << endl;
    cin >> opcion;
    switch(opcion){
      case 1:{
      
        dCenso(personas);
  cout<<"La complejidad es: O(n)"<<endl;
        break;
      }

    

      case 2:{
        ordenamientopilas(desayunoConMamas);
        break;
      }

      case 3:{
     Queue<Persona> priorizada;
       cout << "La complejidad es O(n^3)" << endl;
       for (int i = 0; i < desayunoConMamas.size(); i++ ){ //O(n)
         priorizada.enqueue(desayunoConMamas.get(i)); //
      
        }

        while (!priorizada.is_empty()){
          Persona mayorcito = priorizada.dequeueMin(); //deMIN
          cout<<mayorcito<<endl;
        }
// imprimir a la persona dequeMax
        
        
    
    
    
        break;
      }
      default:{
        cout << "Ingrese una opción válida.";
        break;
      }
      
    }

    
  }
    while (opcion < 1 || opcion > 3);

}

int main(int argc, char**argv) {
  LinkedList<Persona> desayunoConMamas;
  Hashtable<string,Persona>personas(50000);
  
  ifstream archivo;             // O(1)
  archivo.open("bitacora.csv"); // O(1)
  string line;                  // O(1)
  getline(archivo, line);

  while (getline(archivo, line)) {

    string id, first_name, last_name, gender, dob, phone, email, ZIP, city,
        state;
    // O(1)

    // getline(archivo, , , delimitador); //O(1)
    id = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    first_name = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    last_name = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    gender = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    dob = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    phone = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    email = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    ZIP = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    city = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());
    state = line.substr(0, line.find(','));
    line = line.substr(line.find(',') + 1, line.size());

    Persona p(stoi(id), first_name, last_name, gender, dob, phone, email,
              stoi(ZIP), city, state);
    stringstream ss;
    int id_;
    int zip_;
    ss << id;
    ss >> id_;
    stringstream ds;
    ds << ZIP;
    ds >> zip_;
    desayunoConMamas.addLast(p);
    personas.put(city,p);
    }

  
  menu(desayunoConMamas, personas);

  cout << "finito" << endl;  
}