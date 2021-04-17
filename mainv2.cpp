#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <stack>
#include <string>

#define NONE -1

typedef enum COLOR {WHITE, GRAY, BLACK} color; //enum COLOR that represents the color of the given vertex

class Vertex{ // vertex class represents the vertice
private:
    int _id, _maxPath; // id represents the name of the vetice. And the maxPath represents the longest path from the given vetice at a given time
    color _color; // color of the vertice 
    bool _isRoot; // a bool that tells whether the given vetice is a root or not
    std::unique_ptr<std::list<Vertex *>> _adjVertexes; // all the adj vertices
    std:: unique_ptr<std::list<Vertex *>> _parents; // all the parents of a given vertice

public: 
    Vertex(int ID) 
    : _id(ID), _maxPath(1), _color(WHITE), _isRoot(true),
      _adjVertexes(new std::list<Vertex*>),
      _parents(new std::list<Vertex *>) {}

    void setNotRoot(){ 
        _isRoot = false;
    }

    bool isRoot(){
        return _isRoot;
    }

    void addParent(Vertex* parent) {
        _parents->push_back(parent);
    }

    int getId(){
        return _id;
    }

    std::list<Vertex *>* getParents(){
        return _parents.get();
    }

    void setColor(COLOR c){
        _color = c;
    }


    COLOR getColor(){
        return _color;
    }

    void updateMaxPath(int newMax){ // updates the maxPath if the current maxPath is lower than the maxPath given
        if (_maxPath < newMax)
            _maxPath =  newMax;
    }

    int getMaxPath(){
        return _maxPath;
    }

    void addAdjVertex(Vertex *v)
    {
        _adjVertexes->push_back(v);
    }

    std::list<Vertex *> *getAdjVertexes()
    {
        return _adjVertexes.get();
    }
};

class Graph{ // the Graph class represents the Graph that holds all the vertices
private:
    int _size; // the size of the graph, it helps for optimization porposes 
    std::unique_ptr< std::vector< std::unique_ptr<Vertex> > > _vertices; // where all the vertices are stored

public:
    Graph()
    : _size(0),
      _vertices(new std::vector< std::unique_ptr<Vertex> >) {}

    void setSize(int size){
        _size = size;
        _vertices->reserve(_size);
    }

    int getSize(){
        return _size;
    }

    Vertex* getVertex(int index){
        return  (*_vertices)[index].get();
    }

    void addVertex(int id){
        _vertices->push_back( std::unique_ptr<Vertex>(new Vertex(id)) );
    }

    Vertex* operator[](int index){
        return getVertex(index);
    }
};

void getResult(Graph& graph, std::list<int>& roots, int res[2]){ // the getResult function translates the output from the DFS and returns it as the ouput we wanted
    int max = 0;
    int count = 0;

    for (int i : roots){
        Vertex * v = graph[i];
        if(v->getMaxPath() > max)
            max = v->getMaxPath();
        count++;
    }
    res[0] = count; // number of roots
    res[1] = max; // higher maxPath
}

void DFS_search(Graph& graph, int verticeId){
    std::stack<int> verticesStack;
    verticesStack.push(verticeId);

    while (!verticesStack.empty()) {
        Vertex* v = graph[verticesStack.top()];

        if (v->getColor() == WHITE) {
            v->setColor(GRAY);
            std::list<Vertex*> adjList = *(v->getAdjVertexes());

            for (Vertex* adjV : adjList) {
                // there can never be a GRAY adjV since it is a DAG
                if (adjV->getColor() == WHITE) {
                    adjV->addParent(v); // adjV will be responsible for updating the maxPath of another vertex
                    verticesStack.push(adjV->getId());
                }
                // if adjV is BLACK, then the maxPath of the vertex is already known
                else if (adjV->getColor() == BLACK) {
                    v->updateMaxPath(1 + adjV->getMaxPath());
                }
            }
        }
        // if v is GRAY, then its time to update the maxPath of its parents
        else if (v->getColor() == GRAY) {
            v->setColor(BLACK);
            std::list<Vertex *> parentsList = *(v->getParents());

            for (Vertex* parent : parentsList)
                parent->updateMaxPath(1 + v->getMaxPath());
            verticesStack.pop();
        }

        // if v is BLACK, then it is repeated
        else if (v->getColor() == BLACK) {
            verticesStack.pop();
        }
    }
}

void DFS(Graph& graph, std::list<int>& roots){
    int size = graph.getSize();
    for (int i = 0; i < size; i++){
        if (graph[i]->getColor() == WHITE){
            if (graph[i]->isRoot())
                roots.push_back(i);
            DFS_search(graph, i);
        }
    }
}


void processInput(Graph& graph){ // will load the input into the graph class and create the vertices
    int numVertexes, numConnections;
    scanf("%d %d", &numVertexes, &numConnections);
    graph.setSize(numVertexes);
    for (int i = 0; i < numVertexes; i++){
        graph.addVertex(i);
    }

    for (int i = 0; i < numConnections; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        graph[v1 - 1]->addAdjVertex(graph[v2 - 1]);
        graph[v2 - 1]->setNotRoot();
    }
}

int main() // main function
{
    Graph graph;
    processInput(graph);
    std::list<int> roots;
    int result[2];

    DFS(graph, roots);
    getResult(graph, roots, result);

    std::cout << result[0] << " " << result[1] << std::endl; // output
}
