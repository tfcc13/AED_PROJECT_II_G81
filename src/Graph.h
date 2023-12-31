#ifndef PROJECT_II_GRAPH_H
#define PROJECT_II_GRAPH_H

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;
template <class T>
class Vertex {

private:
    T info;                         // contents
    vector<Edge<T>> adj;            // list of outgoing edges
    vector<Edge<T>> incomingEdges;  // list of incoming edges
    bool visited;                   // auxiliary field
    bool processing;                // auxiliary field
    int indegree;                   // auxiliary field
    int num;                        // auxiliary field
    int low;                        // auxiliary field

    void addEdge(Vertex<T> *dest, double w, const string& airline);
    void addIncomingEdge(Vertex<T> *src, double w, const string& airline);
    bool removeEdgeTo(Vertex<T> *d);
    bool removeIncomingEdgeTo(Vertex<T> *s);

public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    const vector<Edge<T>> &getIncomingEdges() const;
    void setAdj(const vector<Edge<T>> &adj);
    void setIncomingEdges(const vector<Edge<T>> &incomingEdges);
    int getIndegree() const;
    void setIndegree(int indegree);
    int getNum() const;
    void setNum(int num);
    int getLow() const;
    void setLow(int low);
    friend class Graph<T>;

};

template <class T>
class Edge {

private:
    Vertex<T>* dest;        // destination vertex
    double weight;          // edge weight
    string airline_;        // for airport connections

public:
    Edge(Vertex<T> *d, double w, const string& airline = "");
    Vertex<T> *getDest() const;
    void setDest(Vertex<T> *dest);
    double getWeight() const;
    void setWeight(double weight);
    string getAirline() const;
    friend class Graph<T>;
    friend class Vertex<T>;

};

template <class T>
class Graph {

private:
    vector<Vertex<T> *> vertexSet;          // vertex set
    int _index_;                            // auxiliary field
    stack<Vertex<T>> _stack_;               // auxiliary field
    list<list<T>> _list_sccs_;              // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;

public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    Vertex<T>* addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, const string& airline = "");
    bool addIncomingEdge(const T &sourc, const T &dest, double w, const string& airline = "");
    bool removeEdge(const T &sourc, const T &dest);
    bool removeIncomingEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;
    void resetIndegree();

    ///Obtains the shortest path possible from an airport to another
    /// \param src Departure airport
    /// \param trg Destination
    /// \return Shortest path between airports
    vector<T> shortestPath(Vertex<T> *src, Vertex<T> *trg) const;

    ///Obtains the shortest path possible from an airport to another, with a filter
    /// \param src Departure airport
    /// \param trg Destination
    /// \param verticesSet Airports that can be passed
    /// \return Shortest path between source and target, using only the desired airports
    vector<T> shortestPathWithFilter(Vertex<T> *src, Vertex<T> *trg, const unordered_set<T> &verticesSet) const;
};

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, const string& airline): dest(d), weight(w), airline_(airline) {}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Vertex<T>::getInfo() const {
    return info;
}

template<class T>
void Vertex<T>::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Vertex<T>::isProcessing() const {
    return processing;
}

template<class T>
void Vertex<T>::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Vertex<T> *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Vertex<T> *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}

template<class T>
string Edge<T>::getAirline() const {
    return airline_;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return visited;
}

template<class T>
int Vertex<T>::getIndegree() const {
    return indegree;
}

template<class T>
void Vertex<T>::setIndegree(int indegree) {
    Vertex::indegree = indegree;
}

template<class T>
int Vertex<T>::getNum() const {
    return num;
}

template<class T>
void Vertex<T>::setNum(int num) {
    Vertex::num = num;
}

template<class T>
int Vertex<T>::getLow() const {
    return low;
}

template<class T>
void Vertex<T>::setLow(int low) {
    Vertex::low = low;
}

template <class T>
void Vertex<T>::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getAdj() const {
    return adj;
}

template<class T>
const vector<Edge<T>> &Vertex<T>::getIncomingEdges() const {
    return incomingEdges;
}

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}

template <class T>
void Vertex<T>::setIncomingEdges(const vector<Edge<T>> &incomingEdges){
    Vertex::incomingEdges = incomingEdges;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 */
template <class T>
Vertex<T>* Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return nullptr;

    Vertex<T>* newVertex = new Vertex<T>(in);
    vertexSet.push_back(newVertex);

    return newVertex;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, const string& airline) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w,airline);
    return true;
}

template <class T>
bool Graph<T>::addIncomingEdge(const T &sourc, const T &dest, double w, const string& airline){
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v2->addIncomingEdge(v1, w, airline);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, const string& airline) {
    adj.push_back(Edge<T>(dest, w, airline));
}

template <class T>
void Vertex<T>::addIncomingEdge(Vertex<T> *src, double w, const string& airline){
    incomingEdges.push_back(Edge<T>(src, w, airline));
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

template <class T>
bool Graph<T>::removeIncomingEdge(const T &sourc, const T &dest){
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v2->removeIncomingEdgeTo(v1);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

template <class T>
bool Vertex<T>::removeIncomingEdgeTo(Vertex<T> *s){
    for (auto it = incomingEdges.begin(); it != incomingEdges.end(); it++)
        if (it->dest == s) {
            incomingEdges.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex<T> *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
template<class T>
vector<T> Graph<T>::topsort() const {
    vector<T> res;
    queue<Vertex<T>*> q;
    if(!this->isDAG()) return res;

    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setIndegree(0);
    }

    for (auto v : vertexSet) {
        for(auto& edge : v->adj) {
            auto w = edge.getDest();
            w->setIndegree(w->getIndegree()+1);
        }
    }

    for(auto v: vertexSet) {
        if(v->indegree == 0) {
            q.push(v);
        }
    }

    while(!q.empty()) {
        auto currVertex = q.front();
        q.pop();
        res.push_back(currVertex->info);
        for(auto& edge : currVertex->adj) {
            auto dest = edge.getDest();
            dest->setIndegree(dest->getIndegree()-1);
            if(dest->getIndegree()== 0) {
                q.push(dest);
            }
        }
    }

    return res;
}

template<class T>
void Graph<T>::resetIndegree() {

    for (auto& v:vertexSet) {
        v->setIndegree(0);
        v->setLow(0);
        v->setProcessing(false);
        v->setNum(0);
        v->setVisited(false);
    }

}

template<class T>
vector<T> Graph<T>::shortestPath(Vertex<T>* src, Vertex<T>* trg) const {
    vector<T> path;
    queue<Vertex<T>*> q;
    unordered_map<Vertex<T>*, Vertex<T>*> predecessors;

    if (src == nullptr || trg == nullptr) {
        // If either source or target vertex is not found, return empty path
        return path;
    }

    for (auto& vertex : vertexSet) {
        vertex->setVisited(false);
    }

    q.push(src);
    src->setVisited(true);

    while (!q.empty()) {
        Vertex<T>* u = q.front();
        q.pop();

        if (u == trg) {
            // Reconstruct path when target vertex is reached
            Vertex<T>* current = trg;
            while (current != nullptr && current != src) {
                path.insert(path.begin(), current->getInfo());
                current = predecessors[current]; // Get predecessor vertex
            }

            if (current == nullptr) {
                // If no path exists from source to target, return empty path
                path.clear();
            } else {
                // Include source vertex in the path
                path.insert(path.begin(), src->getInfo());
            }

            return path;
        }

        for (auto& edge : u->getAdj()) {
            Vertex<T>* v = edge.getDest();

            if (!v->isVisited()) {
                q.push(v);
                v->setVisited(true);
                predecessors[v] = u; // Store predecessor information
            }
        }
    }

    // If target vertex is not reached, return empty path
    return path;
}


template<class T>
vector<T> Graph<T>::shortestPathWithFilter(Vertex<T>* src, Vertex<T>* trg, const unordered_set<T>& verticesSet) const {
    vector<T> path;
    queue<Vertex<T>*> q;
    unordered_map<Vertex<T>*, Vertex<T>*> predecessors;

    if (src == nullptr || trg == nullptr) {
        // If either source or target vertex is not found, return empty path
        return path;
    }

    for (auto& vertex : vertexSet) {
        vertex->setVisited(false);
    }

    q.push(src);
    src->setVisited(true);

    while (!q.empty()) {
        Vertex<T>* u = q.front();
        q.pop();

        if (u == trg) {
            // Reconstruct path when target vertex is reached
            Vertex<T>* current = trg;
            while (current != nullptr && current != src) {
                path.insert(path.begin(), current->getInfo());
                current = predecessors[current]; // Get predecessor vertex
            }

            if (current == nullptr) {
                // If no path exists from source to target, return empty path
                path.clear();
            } else {
                // Include source vertex in the path
                path.insert(path.begin(), src->getInfo());
            }

            return path;
        }

        for (auto& edge : u->getAdj()) {
            Vertex<T>* v = edge.getDest();

            if (!v->isVisited() && verticesSet.find(v->getInfo()) != verticesSet.end()) {
                q.push(v);
                v->setVisited(true);
                predecessors[v] = u; // Store predecessor information
            }
        }
    }

    // If target vertex is not reached, return empty path
    return path;
}


#endif //PROJECT_II_GRAPH_H
