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
    std:: unique_ptr<std::list<Vertice *>> _parents;
    bool _isRoot;
public:
    Vertice(int ID) {
        _id = ID;
        _isRoot = true;
        _parents = std::unique_ptr<std::list<Vertice *>> (new std::list<Vertice *>);
        _color = WHITE;
        _maxPath = 0;
        _adjVertices = std::unique_ptr<std::list<Vertice *>> (new std::list<Vertice*>);
    }

    void setNotRoot(){
        _isRoot = false;
    }

    bool isRoot(){
        return _isRoot;
    }


    void addParent(Vertice* parent) {
        _parents->push_back(parent);
    }

    int getId(){
        return _id;
    }

    std::list<Vertice *>* getParents(){
        return _parents.get();
    }

    void setColor(COLOR c){
        _color = c;
    }


    COLOR getColor(){
        return _color;
    }

    void updateMaxPath(int newMax){
        if (_maxPath < newMax)
            _maxPath =  newMax;
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
    verticesStack.push(verticeId);

    while (!verticesStack.empty()) {
        Vertice* v = graph[verticesStack.top()];

        if (v->getColor() == WHITE) {
            v->setColor(GRAY);    
            std::list<Vertice*> adjList = *(v->getAdjVertices());

            for (Vertice* adjV : adjList) {
                // there can never be a GRAY adjV since it is a DAG
                if (adjV->getColor() == WHITE) {
                    adjV->addParent(v);
                    verticesStack.push(adjV->getId());
                }

                else if (adjV->getColor() == BLACK) {
                    v->updateMaxPath(1 + adjV->getMaxPath());
                }
            }
        } 

        else if (v->getColor() == GRAY) {
            v->setColor(BLACK);
            std::list<Vertice *> parentsList = *(v->getParents());

            for (Vertice* parent : parentsList)
                parent->updateMaxPath(1 + v->getMaxPath());
            verticesStack.pop();
        }

        //if v is BLACK, then it is repeated 
        else if (v->getColor() == BLACK) {
            verticesStack.pop();
        }
    }
}

void DFS(Graph& graph, std::list<int>& possibleRoots){
    int size = graph.getSize();
    for (int i = 0; i < size; i++){
        if (graph[i]->getColor() == WHITE){
            if (graph[i]->isRoot())
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
        graph[v2 - 1]->setNotRoot();
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
