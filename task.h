class Task{
  private:
    string id;
    int value;
  public:
    Task(string id = "", int value = 0){
      this->id = id;
      this->value = value;
    }
    bool operator>(Task & task){
      return (this->value > task.value);
    }
    bool operator<(Task & task){
      return (this->value < task.value);
    }
  friend ostream & operator<<(ostream &, const Task &);
};

 ostream & operator<<(ostream & salida, const Task & task){
   salida << task.id << "#" << task.value;
   return salida;
 }

