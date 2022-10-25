template<typename T>
class Nodo{
    private:
        T data;
        Nodo<T>* left;
        Nodo<T>* right;
        template<typename U>
        friend class BST;
    public:
        Nodo(T data){
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};

template<typename T>
class BST{
  private:
    Nodo<T> * root;
    void insert(Nodo<T> * &elaux, T dato){ //pusimos el & para referenciar que es el aux original
    if( elaux==NULL){
      elaux = new Nodo<T>(dato); //sino hay brazo inserta el nodo
    }else{
      if(dato > elaux->data){
        insert(elaux->right,dato); //con esto ya esta navegando, es decir, se esta movinedo 
      }else if (dato < elaux ->data){
        insert (elaux ->left, dato);
      }else{
        cout<< "igual ... enotnces No se inserta"<<endl;
      }   
      }
    }

void inOrden(Nodo<T>*aux){
  if(aux!=NULL){
    inOrden(aux ->left);
    cout <<aux ->data<<" : ";
    inOrden(aux->right);
  }
}

void PreOrden(Nodo<T>*aux){
  if(aux!=NULL){
    cout <<aux ->data<<" : ";
    PreOrden(aux ->left);
    PreOrden(aux->right);
  }
}

void PosOrden(Nodo<T>*aux){
  if(aux!=NULL){
    PosOrden(aux ->left);
    PosOrden(aux->right);
    cout <<aux ->data<<" : ";
  }
}

  public:
    BST(){
      root = NULL;
    }
  bool isEmpty(){
    return (root ==NULL );
  }
  void insert(T dato){
    if(isEmpty()){
      root = new Nodo<T>(dato);
    }else{
      insert(root, dato);
    }
  }
//la raiz va al incio
void inOrden(){
  inOrden(root);
}

//la raiz va al final
void PosOrden(){
  PosOrden(root);
}

//la raiz va en medio
void PreOrden(){
  PreOrden(root);
}

};