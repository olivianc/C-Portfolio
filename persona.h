#pragma once
#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
using namespace std;
class Persona{
  private:
    string first_name,last_name, gender, dob, city, state, phone, email;
    int  id, zip;
  public:
      Persona(int id = 0, string fname = "", string lname = "", string gender = "", string dob = "", string phone = "", string email = "", int zip = 0, string city = "", string state = ""){
        this->id = id;
        this->first_name = fname;
        this->last_name = lname;
        this->gender=gender;
        this->dob=dob;
        this->phone=phone;
        this->email = email;
        this->zip = zip;
        this->city = city;
        this->state=state;
      }
      bool operator>(Persona & p){
        return (this -> last_name  > p.last_name);
      }

      bool operator<(Persona & p){
        return (this -> zip  < p.zip);
        }

  operator bool() const{
    return id != 0 && first_name != "" &&  last_name != "";
  }

      string getCity(){
        return city;
      }
      string getLastName(){
        return last_name;
      }
      string getFirstName(){
        return first_name;
      }

      int getZip(){
        return zip;
        
      }

    
      
      friend ostream & operator <<(ostream &, const Persona &);

      bool operator>=(const Persona & p){
        return (this -> last_name  > p.last_name);
      }
       bool operator>(const Persona & p){
        return this->last_name.compare(p.last_name) > 0;
      }
      bool operator<=(const Persona & p){
        return (this -> last_name  < p.last_name);
      }



/*
Agrega las sobre cargas de operadores necesarias en la clase Persona.
*/
friend ostream & operator <<(ostream &, const Persona &);
};

ostream & operator <<(ostream & salida, const Persona & persona){
  salida << persona.id << " " << persona.zip<<" "<<persona.first_name<<" "<<persona.last_name<<" "<<persona.city<<endl;
  return salida;  
};
#endif