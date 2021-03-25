#include <iostream>
#include <memory>
#include <vector>
#include <list>

#define NONE -1

typedef enum COLOR {WHITE, GRAY, BLACK} color;

class Vertice{
   private:
      int id;
      Vertice * parent;
      int knocked_count;
      color color;      
   public:
      Vertice(int ID) {
         id = ID;
         parent = NULL;
         color = WHITE;
         knocked_count = 0;
      }
};

class Graph{
   private:
      std::unique_ptr< std::vector< std::unique_ptr<Vertice> > > vertices;
   public:
      Graph(){
         vertices =  std::make_unique< std::vector< std::unique_ptr<Vertice> > >();   
      };
      std::unique_ptr<Vertice> getVertice(int index){
         return  vertices[index];
      }          


};
