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
    Vertice * _parent;
    int _id, _knockedCount, _sendParentCount, _discoveryTime, _endTime;
    color _color;
    std::unique_ptr<std::list<Vertice *>> _adjVertices;
public:
    Vertice(int ID) {
        _id = ID;
        _parent = nullptr;
        _color = WHITE;
        _knockedCount = 0;
        _sendParentCount = 0;
        _adjVertices = std::unique_ptr<std::list<Vertice *>> (new std::list<Vertice*>);
        _discoveryTime = NONE;
        _endTime = NONE;
    }


    int getDiscoveryTime(){
        return _discoveryTime;
    }
    void setDiscoveryTime(int time){
        _discoveryTime = time;
    }

    int getEndTime(){
        return _endTime;
    }
    void setEndTime(int time){
        _endTime = time;
    }

    bool hasParent(){
        return _parent != nullptr;
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

    void addSendParentCount(int n){
        _sendParentCount += n;
    }
    int getSendParentCount(){
        return _sendParentCount;
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
    int _size, _time;
public:
    Graph(){
        _size = 0;
        _time = 0;
        _vertices =  std::unique_ptr< std::vector< std::unique_ptr<Vertice> > > (new std::vector< std::unique_ptr<Vertice> >);
    }
    int getTime(){
        return _time;
    }

    void increaseTime(){
        _time++;
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
    int max = 0;
    int count = 0;

    for (int i : possibleRoots){
        Vertice * v = graph[i];
        if (!v->getParent()){
            if(v->getKnockedCount()> count)
                max = v->getKnockedCount();
            count++;
        }
    }
    res[0] = count;
    res[1] = max;
}

void DFS_search(Graph& graph, int verticeId){
    std::stack<int> verticesStack;
    verticesStack.push(verticeId);

    while (!verticesStack.empty()){
        Vertice * v = graph[verticesStack.top()];
        if (v->getColor() == GRAY){
            v->setEndTime(graph.getTime());
            v->setColor(BLACK);
            verticesStack.pop();
            if (v->hasParent()) {
                v->getParent()->addKnockedCount(v->getSendParentCount());
                v->getParent()->addSendParentCount(v->getSendParentCount());
            }
        }

        else if (v->getColor() == WHITE){
            v->setDiscoveryTime(graph.getTime());
            v->setColor(GRAY);

            std::list<Vertice *> adjList = *(v->getAdjVertices());
            for(Vertice* adjV : adjList){
                adjV->setParent(v);
                if (adjV->getColor() == BLACK && adjV->getEndTime() < graph[verticeId]->getDiscoveryTime()) {
                    v->addKnockedCount(1 + adjV->getKnockedCount());
                    v->addSendParentCount(1 + adjV->getKnockedCount());
                }

                else if(adjV->getColor() == BLACK)
                    v->addKnockedCount(1 + adjV->getKnockedCount());

                else if (adjV->getColor() == WHITE) {
                    v->addKnockedCount(1);
                    v->addSendParentCount(1);
                    verticesStack.push(adjV->getId());
                }
            }
        }
        graph.increaseTime();
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


void processInput(char * input_file, Graph& graph){
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