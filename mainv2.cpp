#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>

#define NONE -1

typedef enum COLOR {WHITE, GRAY, BLACK} color;

class Vertice{
private:
    int _id, _maxPath;
    color _color;
    std::unique_ptr<std::list<Vertice *>> _adjVertices;
    std:: unique_ptr<std::list<int>> _parents;
    bool _isRoot;
public:
    Vertice(int ID) {
        _id = ID;
        _isRoot = true;
        _parents = std::unique_ptr<std::list<int>> (new std::list<int>);
        _color = WHITE;
        _maxPath = 0;
        _adjVertices = std::unique_ptr<std::list<Vertice *>> (new std::list<Vertice*>);
    }

    bool isRoot(){
        return _isRoot;
    }


    void addParent(int parentID) {
        _parents->push_back(parentID);
    }

    int getId(){
        return _id;
    }

    std::list<int>* getParents(){
        return _parents.get();
    }

    void setColor(COLOR c){
        _color = c;
    }


    COLOR getColor(){
        return _color;
    }

    void setMaxPath(int n){
        _maxPath += n;
    }
    int getMaxPath(){
        return _maxPath;
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

void getResult(Graph& graph, std::list<int>& roots, int res[2]){
    int max = 0;
    int count = 0;

    for (int i : roots){
        Vertice * v = graph[i];
        if(v->getMaxPath() > max)
            max = v->getMaxPath();
        count++;
    }
    res[0] = count;
    res[1] = max;
}

void DFS_search(Graph& graph, int verticeId){
    std::stack<int> verticesStack;
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


void processInput(Graph& graph){
    int numVertices, numConnections;
    scanf("%d %d", &numVertices, &numConnections);
    graph.setSize(numVertices);
    for (int i = 0; i < numVertices; i++){
        graph.addVertice(i);
    }

    for (int i = 0; i < numConnections; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        graph[v1 - 1]->addAdjVertice(graph[v2 - 1]);
    }
}

int main()
{
    Graph graph;
    processInput(graph);
    std::list<int> possibleRoots;
    int result[2];

    DFS(graph,possibleRoots);
    getResult(graph,possibleRoots, result);

    std::cout << result[0] << " " << result[1] << std::endl;
}
