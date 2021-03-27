#include <cstdio>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <fstream>
//#include <bits/stdc++.h>

#define NONE -1
#define MAX_INPUT_SIZE 150

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
    Graph(){
        _size = 0;
        _vertices =  std::unique_ptr< std::vector< std::unique_ptr<Vertice> > > (new std::vector< std::unique_ptr<Vertice> >);
    }

    void setSize(int size){
       _size = size;
       _vertices->reserve(_size);
    }

    int getSize(){
        return _size;
    }

    Vertice* getVertice(int index){
        return  (*_vertices)[index].get();
    }

    void addVertice(int id){
        _vertices->push_back( std::unique_ptr<Vertice>(new Vertice(id)) );
    }

    Vertice* operator[](int index){
        return getVertice(index);
    }
};

void getResult(Graph& graph, std::list<int>& possibleRoots, int res[2]){
    in max = possibleRoots.front();
    int count = graph[max]->getKnockedCount();

    for (int i : possibleRoots){
        Vertice * v = graph[i];
        if (!v->getParent() && v->getKnockedCount() > count){
            max = i;
            count = v->getKnockedCount();
        }
    }
    res[0] = max;
    res[1] = count;
}

void DFS_search(Graph& graph, int verticeId){
    std::stack<int> verticesStack;
    verticesStack.push(verticeId);

    while (!verticesStack.empty()){
        Vertice * v = graph[verticesStack.top()];
        if (v->getColor() == GRAY){
            v->setColor(BLACK);
            verticesStack.pop();
            if (v->getParent())
                v->getParent()->addKnockedCount(v->getKnockedCount());
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


void createVertices(int numVertices,Graph& graph){
    for (int i = 0; i< numVertices; i++){
        graph.addVertice(i);
    }
}
/*
void seeLine(std::string line, int result[2]){
   std::istringstream liner(line);
   std::string word;
   liner>>word;
   result[0]= std::stoi(word);
   liner>>word;
   result[1]= std::stoi(word);
}


Graph* ProccessFile(std::string filename){
   std::ifstream file(filename);
   std::string line;
   bool first = true;
   Graph* g;
   //----------------------------------------

   while(getline(file,line)){
      int result[2];
      seeLine(line, result);
      if(first){
         g = new Graph(result[0]);
         createVertices(result[0],*g);
         first = false;
      }
      else{
         g->getVertice(result[0])->addAdjVertice(g->getVertice(result[1]));
      }
   }
   return g;
}

*/
void processInput(char * input_file, Graph& graph){
    FILE *ptrf;
    int numVertices, numConnections;
    char line[MAX_INPUT_SIZE];

    ptrf = fopen("/Users/afonsoalmeida/CLionProjects/test1/file.txt","r");

    fgets(line, sizeof(line)/sizeof(char), ptrf);
    sscanf(line, "%d %d", &numVertices, &numConnections);
    graph.setSize(numVertices);
    for (int i = 0; i < numVertices; i++){
        graph.addVertice(i);
    }

    for (int i = 0; i < numConnections; i++){
        fgets(line, sizeof(line)/sizeof(char), ptrf);
        int v1, v2;
        sscanf(line, "%d %d", &v1, &v2);
        graph[v1 - 1]->addAdjVertice(graph[v2 - 1]);
    }

    fclose(ptrf);

}

int main(int argc, char** argv)
{
    char* fileName =  argv[1];
    Graph graph;
    processInput(fileName, graph);

    std::list<int> possibleRoots;
    int result[2];

    DFS(graph,possibleRoots);
    getResult(graph,possibleRoots, result);

    std::cout << result[0] << " " << result[1] << std::endl;
}

 

