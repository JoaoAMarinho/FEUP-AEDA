#include <iostream>
#include <vector>

using namespace std;

template <class N> class NodeAlreadyExists;
template <class N, class E> class Edge;
template <class N> class NodeDoesNotExist;
template <class N> class EdgeAlreadyExists;
template <class N> class EdgeDoesNotExist;

template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    /**
     * Class Node constructor
     * @param inf - Class member info
     */
    Node(N inf) {
        info = inf;
    }
};

template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    /**
     * Class Edge constructor
     * @param dest - Pointer to the end Node
     * @param val  - Value to be received for change of node
     */
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

template <class N, class E>
class Graph {
    vector< Node<N,E> *> nodes;
public:
    /**
     * Class Graph constructor
     */
    Graph()=default;
    /**
     * Class Graph destructor
     */
    ~Graph()=default;
    /**
     * Function that adds a node to the graph if it does not exist yet
     * @param inf - Info about the node to be added
     * @return - The modified Graph (with the new node if possible)
     */
    Graph & addNode(const N &inf){
        for (int i = 0; i < nodes.size() ; ++i) {
            if (nodes[i]->info==inf) {
                throw NodeAlreadyExists<N>(inf);
            }
        }
        nodes.push_back(new Node<N,E>(inf));
        return *this;
    }
    /**
     * Function that adds an edge to the graph if the initial and final node exist and if there is not an equal edge
     * @param begin - Info about the node the edge starts from
     * @param end - Info about the node the edge reaches
     * @param val - Value to be received in order to make the transition
     * @return - The modified Graph (with the new edge if possible)
     */
    Graph & addEdge(const N &begin, const N &end, const E &val){
        for (int i = 0; i < nodes.size() ; ++i) {
            if (nodes[i]->info==begin){
                for (int j = 0; j < nodes[i]->edges.size(); ++j) {
                    if (nodes[i]->edges[j].destination->info==end){
                        throw EdgeAlreadyExists<N>(begin,end);
                    }
                }
                for (int j = 0; j < nodes.size(); ++j) {
                    if (nodes[j]->info==end){
                        nodes[i]->edges.push_back(*new Edge<N,E> (nodes[j],val));
                        return *this;
                    }
                }
                throw NodeDoesNotExist<N> (end);
            }
        }
        throw NodeDoesNotExist<N> (begin);
    }
    /**
     * Function that removes an edge starting from "begin" and ending in "end", if the actual edge exists and its nodes as well
     * @param begin - Info about the node the edge starts from
     * @param end - Info about the node the edge reaches
     * @return The modified Graph (without the specified edge if possible)
     */
    Graph & removeEdge(const N &begin, const N &end){
        for (int i = 0; i < nodes.size() ; ++i) {
            if (nodes[i]->info==begin){
                for (int j = 0; j < nodes[i]->edges.size(); ++j) {
                    if (nodes[i]->edges[j].destination->info==end){
                        nodes[i]->edges.erase(nodes[i]->edges.begin()+j);
                        return *this;
                    }
                }
                throw EdgeDoesNotExist<N>(begin,end);
            }
        }
        throw NodeDoesNotExist<N> (begin);
    }
    E & edgeValue(const N &begin, const N &end){
        for (int i = 0; i < nodes.size() ; ++i) {
            if (nodes[i]->info==begin){
                for (int j = 0; j < nodes[i]->edges.size(); ++j) {
                    if (nodes[i]->edges[j].destination->info==end){
                        return nodes[i]->edges[j].value;
                    }
                }
                throw EdgeDoesNotExist<N>(begin,end);
            }
        }
        throw NodeDoesNotExist<N> (begin);
    }
    /**
     *
     * @return The number of edges from the Graph
     */
    unsigned numEdges(void) const{
        unsigned sum_edges=0;
        for (int i = 0; i < nodes.size(); ++i) {
            sum_edges+=(*nodes[i]).edges.size();
        }
        return sum_edges;
    }
    /**
     *
     * @return The number of nodes from the Graph
     */
    unsigned numNodes(void) const{
        return nodes.size();
    }
    /**
     *
     * @param os - Output stream to be modified with the information about the Graph
     */
    void print(std::ostream &os) const{
        for (int i = 0; i < nodes.size(); ++i) {
            os<<"( "<<nodes[i]->info;
            for (int j = 0; j < nodes[i]->edges.size(); ++j) {
                os<<"[ "<< nodes[i]->edges[j].destination->info << " " << nodes[i]->edges[j].value << "] ";
            }
            os<<") ";
        }
    }
};

template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g){
    g.print(out);
    return out;
}

// exception NodeAlreadyExists
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    /**
     * Exception NodeAlreadyExists constructor
     * @param inf - The information about the node that already exists
     */
    NodeAlreadyExists(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }

// exception NodeDoesNotExist
template <class N>
class NodeDoesNotExist {
public:
    N info;
    /**
     * Exception NodeDoesNotExist constructor
     * @param inf - The information about the node that does not exist
     */
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }

// exception EdgeAlreadyExists
template <class N>
class EdgeAlreadyExists {
public:
    N info1;
    N info2;
    /**
     * Exception EdgeAlreadyExists constructor
     * @param inf1 - The information about the starting point node
     * @param inf2 - The information about the ending point node
     */
    EdgeAlreadyExists(N inf1,N inf2) {
        info1 = inf1;
        info2=inf2;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeAlreadyExists<N> &no)
{ out << "Edge already exists: " << no.info1<<" , "<<no.info2; return out; }

// exception EdgeDoesNotExist
template <class N>
class EdgeDoesNotExist {
public:
    N info1;
    N info2;
    /**
     * Exception EdgeDoesNotExist constructor
     * @param inf1 - The information about the starting point node
     * @param inf2 - The information about the ending point node
     */
    EdgeDoesNotExist(N inf1,N inf2) {
        info1 = inf1;
        info2=inf2;
    }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const EdgeDoesNotExist<N> &no)
{ out << "Edge does not exist: " << no.info1<<" , "<<no.info2; return out; }


