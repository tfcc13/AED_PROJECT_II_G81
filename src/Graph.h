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
#include <limits>
#include <climits>

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

    bool operator<(const Vertex<T>& v);
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

    /// Finds the reachable airports within a certain distance from a given airport
    ///**Time Complexity:** O(|V|+|E|)
    /// \param source source airport
    /// \param max_stops max distance from the source airport
    /// \return a vector of reachable airports within the given distance
    vector<Vertex<T>*> reachableAirports(Vertex<T>* source, int max_stops) const;
    bool isDAG() const;
    void setIndegree();
    void reset() const;

    ///Obtains the shortest paths possible between a source vertex and a target vertex
    ///**Time Complexity:** O(|V|+|E|)
    ///\param src Source Vertex
    ///\param trg Target Vertex
    ///\return Vector that stores the shortest paths between the vertices, in the form of vectors containing the edges that make the path.
    vector<vector<Edge<T>>> allShortestPaths(Vertex<T> *src, Vertex<T> *trg);


    ///Obtains the shortest paths possible between a source vertex and a target vertex, through a limited set of airlines
    ///**Time Complexity:** O(|V|+|E|)
    ///\param src Source Vertex
    ///\param trg Target Vertex
    ///\param filter Set of airlines that can be in the path
    ///\return Vector that stores the shortest paths between the vertices, in the form of vectors containing the edges that make the path, that respect the filter.
    vector<vector<Edge<T>>> allShortestPathsWithFilter(Vertex<T> *src, Vertex<T> *trg, const unordered_set<string> &filter);


    vector<pair<pair<Vertex<T>*,Vertex<T>*>,int>> maximumStops() const;

    void dfsVisitWithStops(Vertex<T>* v, Vertex<T>*& lastV , int& stops) const;
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
bool Vertex<T>::operator<(const Vertex<T>& v) {
    return this->getLow() - v.getLow();
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


 /// \brief Find reachable airports from a given source airport within a maximum number of stops

 /// \brief This function performs a modified Breadth-First Search (BFS) to identify airports that can
 /// \brief be reached from a specified source airport within a specified maximum number of stops (layovers)

 ///  \brief Key Steps:
 ///  \brief 1. Initialize a BFS queue and vector of reachable airport vertices pointers to track visited airports. Reset vertices
 ///  \brief 2. Enqueue the source airport and mark it as visited
 ///  \brief 3. While the queue is not empty and the number of stops is within the limit:
 ///      \brief a. Process the current airport and enqueue its unvisited adjacent airports;
 ///      \brief b. Track the depth (stops) to control the number of stops.
 ///
 /// \param source The source airport vertex
 /// \param max_stops The maximum number of stops allowed
 /// \return vector of reachable airport vertices pointers

template<class T>
vector<Vertex<T>*> Graph<T>::reachableAirports(Vertex<T>* source, int max_stops) const {

    queue<Vertex<T>*> q;
    vector<Vertex<T>*> reachableAirports_vec;

    int number_of_stops = 0;

    for(auto v : vertexSet){
        v->visited = false;
    }

    q.push(source);
    source->visited = true;

    while(!q.empty() and number_of_stops <= max_stops){

        int number_of_airports_per_depth = int(q.size());

        for(int i = 0; i < number_of_airports_per_depth; i++){

            auto v = q.front();
            q.pop();
            reachableAirports_vec.push_back(v);

            for (auto & e : v->adj) {
                auto w = e.dest;
                if ( ! w->visited ) {
                    q.push(w);
                    w->visited = true;
                }
            }

        }

        number_of_stops++;

    }

    reachableAirports_vec.erase(reachableAirports_vec.begin());
    return reachableAirports_vec;

}

template<class T>
void Graph<T>::reset() const {

    for (auto& v:vertexSet) {
        v->setLow(0);
        v->setProcessing(false);
        v->setNum(0);
        v->setVisited(false);
    }
}

template<class T>
void Graph<T>::setIndegree() {
    for (auto& v : vertexSet) {
        v->setIndegree(int(v->getIncomingEdges().size()));
        v->setLow(0);
        v->setProcessing(false);
        v->setNum(0);
        v->setVisited(false);
    }
}

template<class T>
vector<vector<Edge<T>>> Graph<T>::allShortestPaths(Vertex<T> *src, Vertex<T> *trg) {
    vector<vector<Edge<T>>> allPaths;
    int desiredSize = INT_MAX;
    queue<pair<Vertex<T>*, vector<Edge<T>>>> q;
    q.push({src, {}}); // Start with an empty path

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        Vertex<T>* currentVertex = current.first;
        vector<Edge<T>> currentPath = current.second;

        // 1st BFS solution; we know that this an optimal path; update desiredSize
        if (allPaths.empty() && currentVertex == trg) {
            desiredSize = currentPath.size();
            allPaths.push_back(currentPath);
            continue;
        }

        if (currentPath.size() == desiredSize && currentVertex == trg) {
            allPaths.push_back(currentPath);
            continue; // Skip exploring further if the desired size and target are reached
        }

        if (currentPath.size() >= desiredSize || currentVertex == trg) {
            continue; // Skip exploring further if the path exceeds the desired size or reaches the target
        }

        for (Edge<T> e : currentVertex->getAdj()) {
            Vertex<T>* nextVertex = e.getDest();
            vector<Edge<T>> nextPath = currentPath;
            nextPath.push_back(e); // Extend the current path

            q.push({nextVertex, nextPath}); // Add the next vertex and extended path to the queue
        }
    }
    return allPaths;
}

template<class T>
vector<vector<Edge<T>>> Graph<T>::allShortestPathsWithFilter(Vertex<T> *src, Vertex<T> *trg, const unordered_set<string>& filter) {
    vector<vector<Edge<T>>> allPaths;
    int desiredSize = INT_MAX;
    queue<pair<Vertex<T>*, vector<Edge<T>>>> q;
    q.push({src, {}}); // Start with an empty path

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        Vertex<T>* currentVertex = current.first;
        vector<Edge<T>> currentPath = current.second;


        // 1st BFS solution; we know that this an optimal path; update desiredSize
        if (allPaths.empty() && currentVertex == trg) {
            desiredSize = currentPath.size();
            allPaths.push_back(currentPath);
            continue;
        }

        if (currentPath.size() == desiredSize && currentVertex == trg) {
            allPaths.push_back(currentPath);
            continue; // Skip exploring further if the desired size and target are reached
        }

        if (currentPath.size() >= desiredSize || currentVertex == trg) {
            continue; // Skip exploring further if the path exceeds the desired size or reaches the target
        }

        for (Edge<T> e : currentVertex->getAdj()) {
            auto it = find(filter.begin(), filter.end(), e.getAirline());
            if (it == filter.end()) continue;
            Vertex<T>* nextVertex = e.getDest();
            vector<Edge<T>> nextPath = currentPath;
            nextPath.push_back(e); // Extend the current path

            q.push({nextVertex, nextPath}); // Add the next vertex and extended path to the queue
        }
    }
    return allPaths;
}

template<class T>
vector<pair<pair<Vertex<T>*,Vertex<T>*>,int>> Graph<T>::maximumStops() const {

    vector<pair<pair<Vertex<T>*,Vertex<T>*>,int>> res;

    int maxStops = 0;
    Vertex<T>* firstVert = nullptr;
    Vertex<T>* lastVert = nullptr;

    for(auto v: vertexSet) {
        firstVert = v;
        int stops = 0;
        Graph<T>::reset();
        //if(!v->isVisited()) {
            dfsVisitWithStops(v,lastVert,stops);
            if(stops > maxStops) {
                maxStops = stops;
                res.clear();
                res.push_back(make_pair(make_pair(firstVert,lastVert),stops));
            }
            else if(stops == maxStops) {
                res.push_back(make_pair(make_pair(firstVert,lastVert),stops));
          //  }
        }
    }

    return res;


}
template<class T>
void Graph<T>::dfsVisitWithStops(Vertex<T>* v, Vertex<T>*& lastV , int& stops) const {
    v->setVisited(true);
    stops++;

    for(auto& edge : v->getAdj()) {
        auto dest = edge.getDest();
        lastV = dest;
        if(!dest->isVisited()) {
            dfsVisitWithStops(dest, dest, stops);
        }
    }
}


#endif //PROJECT_II_GRAPH_H
