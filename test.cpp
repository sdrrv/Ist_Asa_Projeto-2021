#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <vector>
#include <list>
#include <stack>

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
      int getKnockedCount(){
         return _knockedCount;
      }

      void addAdjVertice(Vertice *v)
      {
         _adjVertices->push_back(v);
      }

      std::list<Vertice *> *getAdjVertices()
      {
         return _adjVertices.get();
      }
};

class Graph{
   private:
      std::unique_ptr< std::vector< std::unique_ptr<Vertice> > > _vertices;
      int _size;
   public:
      Graph(int size){
         _size = size;
         _vertices =  std::make_unique< std::vector< std::unique_ptr<Vertice> > >();   
         _vertices->reserve(size);
      }
      
      int getSize(){
         return _size;
      }

      Vertice* getVertice(int index){
         return  (*_vertices)[index].get();
      }          
      
      void addVertice(int id){
         _vertices->push_back( std::make_unique<Vertice>(id) );
      }

      Vertice* operator[](int index){
         return getVertice(index);  
      }
};

int* getResult(Graph& graph, std::list<int>& possibleRoots){
   int max = possibleRoots.front();
   int count = graph[max]->getKnockedCount();

   for (int i : possibleRoots){
      Vertice * v = graph[i];
      if (!v->getParent() && v->getKnockedCount() > count){
         max = i;
         count = v->getKnockedCount();
      }
   }
   int res[2] = {max, count};
   return res;
}

void DFS_search(Graph& graph, int verticeId){
   std::stack<int> verticesStack;
   verticesStack.push(verticeId);
   
   while (!verticesStack.empty()){
      Vertice * v = graph[verticesStack.top()];
      if (v->getColor() == GRAY){ 
         v->setColor(BLACK);
         v->getParent()->addKnockedCount(v->getKnockedCount());
         verticesStack.pop(); 
      }      

      else if (v->getColor() == WHITE){
         v->setColor(GRAY);
         
         std::list<Vertice *> adjList = *(v->getAdjVertices());
         for(Vertice* adjV : adjList){
            if (adjV->getColor() == BLACK){
               v->addKnockedCount(adjV->getKnockedCount());
            }
            else {
               v->addKnockedCount(1);
               adjV->setParent(v);
               verticesStack.push(adjV->getId());
            }
         }
      }
   }

}

void DFS(Graph& graph, std::list<int>& possibleRoots){
   int size = graph.getSize();
   for (int i = 0; i < size; i++){
      if (graph[i]->getColor() == WHITE){
         possibleRoots.push_back(i);
         DFS_search(graph, i);
      }
   }
}

int main(){        
}
