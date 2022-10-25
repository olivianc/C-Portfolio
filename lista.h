#pragma once
#ifndef LISTA_H
#define LISTA_H
#include <iostream>
using namespace std;
template <typename T> class Node {
private:
  T data;
  Node<T> *next;
  Node<T> *previous;
  template <typename U> friend class LinkedList;

public:
  Node(T data, Node<T> *next, Node<T> *previous) {
    this->data = data;
    this->next = next;
    this->previous = previous;
  }
};

template <typename T> class LinkedList {
private:
  Node<T> *head;
  Node<T> *last;
  int _size;

public:
  LinkedList() {
    head = last = nullptr;
    _size = 0;
  }
  LinkedList(int size) : LinkedList() {

    for (int i = 0; i < size; i++) {
      T dato;
      addLast(dato);
    }
  }
  /*
  Método para agregar un nodo al inicio de la lista.
  */
  void addFirst(T dato) {
    _size++;
    // SORT the code:
    Node<T> *nuevo = new Node<T>(dato, nullptr, nullptr);
    if (!head && !last) { // si es vacía la lista
      head = last = nuevo;
    } else {
      nuevo->next = head;
      head->previous = nuevo;
      head = nuevo;
    }
  }
  /*
  Método imprime todos los nodos de la lista
  */
  void print() {
    Node<T> *aux = head;
    while (aux) {
      cout << aux->data << endl;
      aux = aux->next;
    }
  }
  /*
  Método imprime todos los nodos de la lista
  */
  void reverse() {
    Node<T> *aux = last;
    while (aux) {
      cout << aux->data << endl;
      aux = aux->previous;
    }
  }

  /*
  Método que regresa 1, si la lista no tiene elementos.
  */
  bool is_empty() { return !head; }
  /*
  Método para agregar un nodo al final de la lista.
  */
  void addLast(T dato) {
    _size++;
    Node<T> *nuevo = new Node<T>(dato, nullptr, nullptr);
    if (is_empty()) {
      head = last = nuevo; // addFirst(dato)
    } else {
      last->next = nuevo;
      nuevo->previous = last;
      last = nuevo;
    }
  }
  /*
  Método para calcular el tamaño de la lista, cuántos elementos tenemos.
  */
  int size() { return this->_size; }

  /*
  Método para revisar si existe un elemento, regresa 1 si existe o 0 sino
  existe.
  */
  bool contains(T data) {
    Node<T> *temp = head;
    bool exists = 0;
    while (temp && exists == 0) {
      if (data == temp->data) {
        exists = 1;
      }
      temp = temp->next;
    }
    return exists;
  }

  /*
  Método para obtener un elemento que se encuentra en una posición: "index".
  Si index es menor a 0 o mayor al tamaño se lanza exception.
  */
  T get(int index) {
    if (index < 0 || index > size())
      throw -1;
    Node<T> *temporal = head;
    for (int i = 0; i < index; i++) {
      temporal = temporal->next;
    }
    return temporal->data;
  }
  T &operator[](int index) {
    if (index < 0 || index > size())
      throw -1;
    Node<T> *temporal = head;
    for (int i = 0; i < index; i++) {
      temporal = temporal->next;
    }
    return temporal->data;
  }
  /*
  Método para remover de la lista el primer elemento, si la lista NO es vacía
  se puede realizar.  */
  T remove_front() {
    if (is_empty()) {
      throw -1;
    } else if (head == last) {
      // 1 nodo
      T dato = head->data; // sacar dato
      delete head;         // borrar nodo
      head = last = nullptr;
      _size--;
      return dato;
    } else {
      // minimo 2 nodos
      T dato = head->data;
      head = head->next;
      delete head->previous;
      head->previous = nullptr;
      _size--;
      return dato;
    }
  }

  /*
  Método para remover de la lista el último elemento, si la lista NO es vacía
  se puede realizar.  */
//O(1)
  T remove_last() {
    if (is_empty()) {
      throw -1;
    } else if (head == last) {
      // 1 nodo
      T dato = head->data; // sacar dato
      delete head;         // borrar nodo
      head = last = nullptr;
      _size--;
      return dato;
    } else {
      // minimo 2 nodos
      T dato = last->data;
      last = last->previous;
      delete last->next;
      last->next = nullptr;
      _size--;
      return dato;
    }
  }

  /*
  Obtiene el dato guardado en el último nodo
  */
  T getFirst() {
    if (is_empty()) {
      throw 1;
    }
    return head->data;
  }

  /*
  Obtiene el dato guardado en el último nodo
  */
  T getLast() {
    if (is_empty()) {
      throw 1;
    }
    return last->data;
  }

  /*
  Método para remover de la lista el último elemento, si la lista NO es vacía
  se puede realizar.  */
  T remove(int index) {
    if (is_empty()) {
      throw -1;
    } else if (index == 0) {
      return remove_front();
    } else if (index == _size - 1) {
      return remove_last();
    } else {
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      // minimo 2 nodos
      T dato = aux->data;
      aux->previous->next = aux->next;
      aux->next->previous = aux->previous;
      aux->next = nullptr;
      aux->previous = nullptr;
      delete aux;
      _size--;
      return dato;
    }
  }
  friend ostream &operator<<(ostream &out, LinkedList<T> &l) {
    for (int i = l.size() - 1; i >= 0; i--) {
      T dato = l.get(i);
      out << " | ";
      out << dato;
      out << " | ";
    }
    cout << "\n";
    return out;
  }
  void insert(T dato, int index) {
    if (is_empty()) {
      throw -1;
    } else if (index < 0 && index >= _size) {
      throw -1;
    } else {
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      // minimo 2 nodos
      Node<T> *n = new Node<T>(dato, nullptr, nullptr);
      n->next = aux;
      n->previous = aux->previous;
      aux->previous = n;
      n->previous->next = n;
      _size++;
      return dato;
    }
  }
};

template <typename T> class Queue : public LinkedList<T> {
public:
  Queue() : LinkedList<T>() {}
  void enqueue(T dato) { LinkedList<T>::addLast(dato); }
  T dequeue() { return LinkedList<T>::remove_front(); }
  T peek() { return LinkedList<T>::getFirst(); }
  bool is_empty() { return LinkedList<T>::is_empty(); }
  int size() { return LinkedList<T>::size(); }
  
int getMax(){
  T maximoDecimusMeridious = LinkedList<T>::getFirst();
  int posicion = 0;
  for(int i = 0; i < LinkedList<T>::size(); i++ ){
    if( LinkedList<T>::get(i) > maximoDecimusMeridious ){
        maximoDecimusMeridious = LinkedList<T>::get(i);
        posicion = i;
      }
    }
  
  return posicion;
}
int getMin(){
  T minimunDecimusMeridious = LinkedList<T>::getFirst();
  int posicion = 0;
  for(int i = 0; i < LinkedList<T>::size(); i++ ){
    if( LinkedList<T>::get(i) < minimunDecimusMeridious ){
        minimunDecimusMeridious = LinkedList<T>::get(i);
        posicion = i;
      }
    }
  return posicion;
}
T dequeueMax(){
  return LinkedList<T>::remove(getMax());
}
T peekMax(){
  return LinkedList<T>::get(getMax());
}
T dequeueMin(){
  return LinkedList<T>::remove(getMin());
}
T peekMin(){
  return LinkedList<T>::get(getMin());
}


};

template <typename T> class Stack : public LinkedList<T> {
public:
  Stack() : LinkedList<T>() {}
  void push(T dato) { LinkedList<T>::addLast(dato); }
  T pop() { return LinkedList<T>::remove_last(); }
  T peek(){
  return LinkedList<T>::getLast();
}
};

#endif