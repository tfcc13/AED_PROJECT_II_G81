//
// Created by tiago on 16-12-2023.
//

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


/****************** Provided structures  ********************/

template <class T>
class Vertex {
    T info;                // contents
    vector<Edge<T> > adj;  // list of outgoing edges
    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int indegree;          // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field

    void addEdge(Vertex<T> *dest, double w, const string& airline);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    void setInfo(T in);
    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Edge<T>> &getAdj() const;
    void setAdj(const vector<Edge<T>> &adj);

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
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
    string airline_;    // for airport connections
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
    vector<Vertex<T> *> vertexSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Vertex<T>> _stack_;           // auxiliary field
    list<list<T>> _list_sccs_;        // auxiliary field

    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    bool dfsIsDAG(Vertex<T> *v) const;
public:
    Vertex<T> *findVertex(const T &in) const;
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, const string& airline = "");
    bool removeEdge(const T &sourc, const T &dest);
    vector<Vertex<T> * > getVertexSet() const;
    vector<T> dfs() const;
    vector<T> dfs(const T & source) const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
    bool isDAG() const;

    ///Obtains the shortest path possible from an airport to another
    /// \param source Departure airport
    /// \param target Destination
    /// \return Shortest path between airports
    vector<T> shortestPath(const T &source, const T &target) const;

    ///Obtains the shortest path possible from an airport to another, with a filter
    /// \param source Departure airport
    /// \param target Destination
    /// \param verticesSet Airports that can be passed
    /// \return Shortest path between source and target, using only the desired airports
    vector<T> shortestPathWithFilter(const T &source, const T &target, const unordered_set<T> &verticesSet) const;
};

/****************** Provided constructors and functions ********************/

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

template <class T>
void Vertex<T>::setAdj(const vector<Edge<T>> &adj) {
    Vertex::adj = adj;
}


/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Vertex<T>(in));
    return true;
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

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, const string& airline) {
    adj.push_back(Edge<T>(d, w,airline));
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


/****************** DFS ********************/
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


/****************** DFS ********************/
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


/****************** BFS ********************/
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


/****************** isDAG  ********************/
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

/**
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


/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
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
vector<T> Graph<T>::shortestPath(const T& source, const T& target) const {
    vector<T> path;
    queue<Vertex<T>*> q;

    Vertex<T>* src = findVertex(source);
    Vertex<T>* trg = findVertex(target);

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
                current = findVertex(current->getNum()); // Get predecessor vertex by number
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
                v->setNum(u->getNum()); // Set predecessor information
            }
        }
    }

    // If target vertex is not reached, return empty path
    return path;
}


template<class T>
vector<T> Graph<T>::shortestPathWithFilter(const T& source, const T& target, const unordered_set<T>& verticesSet) const {
    vector<T> path;
    queue<Vertex<T>*> q;

    Vertex<T>* src = findVertex(source);
    Vertex<T>* trg = findVertex(target);

    if (src == nullptr || trg == nullptr || verticesSet.find(source) == verticesSet.end() || verticesSet.find(target) == verticesSet.end()) {
        // If either source or target vertex is not found, or they are not in the vertices set, return empty path
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
                current = findVertex(current->getNum()); // Get predecessor vertex by number
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
                v->setNum(u->getNum()); // Set predecessor information
            }
        }
    }

    // If target vertex is not reached, return empty path
    return path;
}


#endif //PROJECT_II_GRAPH_H
