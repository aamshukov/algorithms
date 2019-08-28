//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_GRAPH_H__
#define __ALGORITHMS_GRAPH_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename T>
class graph : private noncopyable
{
    public:
        using value_type = T;
        using values_type = std::vector<value_type>;

        using index_type = int;
        using size_type = int;

    private:
        struct vertex
        {
            index_type id = 0;
            value_type value = value_type();
        };

        using vertex_type = std::shared_ptr<vertex>;
        using vertices_type = std::list<vertex_type>;

        struct edge
        {
            index_type id = 0;
            vertices_type endpoints; // usually has two vertices and more vertices in hyper-graphs
        };

        using edge_type = std::shared_ptr<edge>;
        using edges_type = std::vector<edge_type>;

    private:
        vertices_type           my_vertices;
        edges_type              my_edges;

    public:
                                graph();
                               ~graph();

        const vertices_type&    vertices() const;
        const edges_type&       edges() const;

        bool                    add_edge(const edge_type& edge);
};

template <typename T>
graph<T>::graph()
{
}

template <typename T>
graph<T>::~graph()
{
    my_vertices.clear();
    my_edges.clear();
}

template <typename T>
inline const typename graph<T>::vertices_type& graph<T>::vertices() const
{
    return my_vertices;
}

template <typename T>
inline const typename graph<T>::edges_type& graph<T>::edges() const
{
    return my_edges;
}

template <typename T>
bool graph<T>::add_edge(const typename graph<T>::edge_type& edge)
{
    bool result = true;

    return true;
}

END_NAMESPACE

#endif // __ALGORITHMS_GRAPH_H__
