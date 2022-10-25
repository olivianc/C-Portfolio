#pragma once
#define HASHTABLE_H
#include "lista.h"
#include <algorithm>
#include <functional>
#include <vector>

template <typename K, typename T> /* K key, T value*/
class HashPair {
public:
  K key;
  T value;
  HashPair(K key, T value) {
    this->key = key;
    this->value = value;
  }
  HashPair() {}
};

template <typename K, typename T> class Hashtable {
private:
  int size;
  LinkedList<HashPair<K, T> *> *tabla;
  int fh(K key) const {
    hash<K> khash;
    return khash(key) % size;
  }

public:
  Hashtable(int size = 20) {
    this->size = size;
    tabla = new LinkedList<HashPair<K, T> *>[size];
    for (int i = 0; i < size; i++)
      tabla[i] = LinkedList<HashPair<K, T> *>();
  }

  bool put(K key, T value) {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
      if (lista.get(i)->key == key) {
        indice = i;
      }
    }
    tabla[posicion].addLast(new HashPair<K, T>(key, value));
    return (indice >= 0) ? 0 : 1;
  }

  T get_or_default(K key, const T value) const {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> &lista = tabla[posicion];
    // int i = 0;
    // for (int i = 0; i < lista.size(); i++) {
    for (int i = 0; i < lista.size(); i++) {
      if (lista.get(i)->key == key) {
        // lista.remove(i);
        return lista.get(i)->value;
      }
    }
    return value;
  }

  bool remove(K key) {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> & lista = tabla[posicion];
    /* do{
       if(key==lista.get(i)->key){
         lista.remove(i);
         return true;
       }else{
         i++;
         return false;
       }
     }while(i!=lista.size() || key==lista.get(i)->key);
   }*/
    for (int i = 0; i < lista.size(); i++) {
      if (lista.get(i)->key == key) {
        lista.remove(i);
        return true;
      }
    }
    return false;
  }

  /*
    T get(K key) const {
      int posicion = fh(key);
      LinkedList<HashPair<K, T> *> lista = tabla[posicion];
      int i = 0;
      while (lista.get(i)->key != key) {
        i++;
      }
      if (i >= lista.size()) {
        throw -1;
      }
      return lista.get(i)->value;
    } */

  bool contains(K key) const {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    for (int i = 0; i < lista.size(); i++) {
      if (lista.get(i)->key == key) {
        return 1;
      }
    }
    return 0;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < tabla[i].size(); j++) {
        cout << "i:" << i << " k: " << tabla[i].get(j)->key << "  "
             << tabla[i].get(j)->value << endl;
      }
    }
  }

  LinkedList<T> keysT() const {
    LinkedList<T> sortedkeys;
    LinkedList<HashPair<K, T> *> lista;
    int i = 0;
    while (i < size) {
      sortedkeys.addFirst(lista.get(i)->key);
      i++;
    }
    sort(sortedkeys.begin(), sortedkeys.end());
    return sortedkeys;
  }

  LinkedList<K> keysK() const {
    std::vector<K> ks;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < tabla[i].size(); j++) {
        K key = tabla[i].get(j)->key;
        if (!count(ks.begin(), ks.end(), key))
          ks.push_back(key);
      }
    }
    sort(ks.begin(), ks.end());
    LinkedList<K> kays;
    while (!ks.empty()) {
      kays.addFirst(ks.back());
      ks.pop_back();
    }
    return kays;
  }

  friend ostream &operator<<(ostream &out, const Hashtable &h) {
    LinkedList<K> ks = h.keys();
    while (!ks.is_empty()) {
      K key = ks.remove_front();
      int pos = h.fh(key);
      out << "____\t" << key << "\t____\n";
      for (int i = 0; i < h.tabla[pos].size(); i++) {
        if (h.tabla[pos].get(i).key == key) {
          T p = h.tabla[pos].get(i).value;
          out << p << "\n";
        }
      }
    }
    return out;
  }
  void pSizeKeys() {
    LinkedList<K> ks = keysK();
    while (!ks.is_empty()) {
      K key = ks.remove_front();
      int pos = fh(key), count = 0;
      cout << "-\t" << key << ": ";
      for (int i = 0; i < tabla[pos].size(); i++) {
        if (tabla[pos].get(i).key == key)
          count++;
      }
      cout << count << "\n";
    }
  }

  // duda
  /*
    int size()const{

    }
  */
};