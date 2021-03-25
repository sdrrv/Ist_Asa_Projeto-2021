#include <iostream>
#include <memory>
#include <vector>
#include <list>

#define NONE -1

typedef enum COLOR {WHITE, GRAY, BLACK} color;

class Vertice{
   private:
      int _id;
      Vertice * _parent;
      int _knockedCount;
      color _color;
      std::unique_ptr<std::list<Vertice *>> _adjVertices;
   public:
      Vertice(int ID) {
         _id = ID;
         _parent = NULL;
         _color = WHITE;
         _knockedCount = 0;
         _adjVertices = std::make_unique<std::list<Vertice *>>();
      }

      void setParent(Vertice * p) {
         _parent = p;
      }

      Vertice * getParent(){
         return _parent;
      }

      void setColor(COLOR c){
         _color = c;
      }

      COLOR getColor(){
         return _color;
      }

      void addKnockedCount(int n){
         _knockedCount += n;
      }
      
      void addAdjVertice(Vertice * v){
         _adjVertices->push_back(v);
      } 
      
      std::list<Vertice *> * getAdjVertices(){
         return _adjVertices.get();
      }

};

class Graph{
   private:
      std
};
