#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
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

      int getId(){
         return _id;
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
      std::unique_ptr< std::vector< std::unique_ptr<Vertice> > > vertices;
   public:
      Graph(){
         vertices =  std::make_unique< std::vector< std::unique_ptr<Vertice> > >();   
      }

      Vertice* getVertice(int index){
         return  (*vertices)[index].get();
      }          
      
      void addVertice(int id){
         vertices->push_back( std::make_unique<Vertice>(id) );
      }

      Vertice* operator[](int index){
         return getVertice(index);  
      }
};

int main(){        
   Graph g;
   for (int id = 0; id < 3; id++)
      g.addVertice(id);
   g[0]->addAdjVertice(g[1]);
   
   g[0]->addAdjVertice(g[2]);
   g[1]->addAdjVertice(g[2]);
   g[2]->addAdjVertice(g[0]);
   std::cout << "VERTICE 0" << std::endl;
   std::list<Vertice *> hey = *(g[0]->getAdjVertices());
   for(Vertice * x : hey)
      std::cout << x->getId() << std::endl;
   std::list<Vertice *> hei = *(g[1]->getAdjVertices());
   for(Vertice * x : hei)
      std::cout << x->getId() << std::endl;
   std::list<Vertice *> heo = *(g[0]->getAdjVertices());
   for(Vertice * x : heo)
      std::cout << x->getId() << std::endl;
}
