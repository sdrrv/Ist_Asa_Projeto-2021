#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

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
         _adjVertices = std::unique_ptr<std::list<Vertice *>> (new std::list<Vertice*>);
      }
      bool hasParent(){
         return _parent != NULL;
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
         _vertices =  std::unique_ptr< std::vector< std::unique_ptr<Vertice> > > (new std::vector< std::unique_ptr<Vertice> >);   
         _vertices->reserve(size);
      }
      
      int getSize(){
         return _size;
      }

      Vertice* getVertice(int index){
         return  (*_vertices)[index-1].get();
      }          
      
      void addVertice(int id){
         _vertices->push_back( std::unique_ptr<Vertice>(new Vertice(id)) );
      }

      Vertice* operator[](int index){
         return getVertice(index);  
      }
};

void getResult(Graph& graph, std::list<int>& possibleRoots, int res[2]){
   std::cout<<"Getting Results"<< std::endl;
   int max = possibleRoots.front();
   int count = graph[max]->getKnockedCount();
   std::list<int> finalList = std::list<int>();

   for (int i : possibleRoots){
      Vertice * v = graph[i];
      if (!v->getParent()){
         std::cout<<"Here: "<< v->getId() << v->getAdjVertices()->size() <<std::endl;
         if(v->getKnockedCount()>count)
            count = v->getKnockedCount();
         finalList.push_back(i);
      }
   }
   res[0] = finalList.size();
   res[1] = count;
}

void DFS_search(Graph& graph, int verticeId){
   std::cout<<"Searhing vertice " << verticeId << std::endl;
   std::stack<int> verticesStack;
   verticesStack.push(verticeId);
   
   while (!verticesStack.empty()){
      std::cout<<"Stack Size: "<<verticesStack.size()<< std::endl;
      Vertice * v = graph[verticesStack.top()];
      if (v->getColor() == GRAY){ 
         v->setColor(BLACK);
         if(v->hasParent())
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
   std::cout<<"Starting DFS"<< std::endl;
   int size = graph.getSize();
   for (int i = 1; i < size; i++){
      if (graph[i]->getColor() == WHITE){
         std::cout<<"White"<< std::endl;
         possibleRoots.push_back(i);
         DFS_search(graph, i);
      }
   }
}


void createVertices(int numVertices,Graph& graph){
   for (int i = 1; i< numVertices+1; i++){
      graph.addVertice(i);
   }
}

void seeLine(std::string line, int result[2]){
   std::istringstream liner(line);
   std::string word;
   liner>>word;
   result[0]= std::stoi(word);
   liner>>word;
   result[1]= std::stoi(word);
}



Graph* ProccessFile(std::string filename){
   
   std::cout<<"ProccessFile"<< std::endl;
   std::ifstream file(filename);
   std::string line;
   bool first = true;
   Graph* g;
   //----------------------------------------

   while(getline(file,line)){
      int result[2];
      std::cout<<"Getting Line: "<< line << std::endl;
      seeLine(line, result);
      if(first){
         std::cout<<"---------"<< std::endl;
         g = new Graph(result[0]);
         createVertices(result[0],*g);
         first = false;
      }
      else{
         g->getVertice(result[0])->addAdjVertice(g->getVertice(result[1]));
      }
   }  
   std::cout<<"All Good so far"<< std::endl;
   return g;
}

int main(int argc, char** argv){
   std::cout<<"Starting"<< std::endl;
   //std::string fileName =  argv[1];
   Graph * graph = ProccessFile("test.in");
   std::list<int> possibleRoots;
   int result[2];

   DFS(*graph,possibleRoots);
   getResult(*graph,possibleRoots, result);

   std::cout <<"Result: "<< result[0] <<" "<< result[1]<< std::endl;

   delete graph;   
}
