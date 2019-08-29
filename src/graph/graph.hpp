//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_GRAPH_H__
#define __ALGORITHMS_GRAPH_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename VType, typename EType, std::size_t N = 2>
class graph : private noncopyable
{
    public:
        using vertex_value_type = VType;
        using edge_value_type = EType;

        using index_type = int;
        using size_type = int;

        struct vertex
        {
            index_type id = 0;
            vertex_value_type value = vertex_value_type();
        };

        using vertex_type = std::shared_ptr<vertex>;

        struct vertex_key_comparator
        {
            bool operator() (const vertex_type& lhs, const vertex_type& rhs) const
            {
                return (*lhs).id < (*rhs).id;
            }
        };

        using vertices_type = std::set<vertex_type, vertex_key_comparator>;

        struct edge
        {
            index_type id = 0;
            edge_value_type value = edge_value_type();

            vertex_type endpoints[N]; // usually has two vertices and more vertices in hyper-graphs
        };

        using edge_type = std::shared_ptr<edge>;

        struct edge_key_comparator
        {
            bool operator() (const edge_type& lhs, const edge_type& rhs) const
            {
                return (*lhs).id < (*rhs).id;
            }
        };

        using edges_type = std::set<edge_type, edge_key_comparator>;

        using ve_map_type = std::map<vertex_type, edge_type, vertex_key_comparator>;

        using counter_type = counter;

    private:
        vertices_type                   my_vertices;
        counter_type                    my_vertices_counter;

        edges_type                      my_edges;
        counter_type                    my_edges_counter;

        ve_map_type                     my_ve_map; // mapping vertex to edge

    public:
                                        graph();
                                       ~graph();

        const vertices_type&            vertices() const;
        const edges_type&               edges() const;

        std::pair<vertex_type, bool>    add_vertex(const vertex_value_type& value);
        std::pair<vertex_type, bool>    add_vertex(const vertex_type& new_vertex);

        std::pair<vertex_type, bool>    remove_vertex(const index_type& id);

        std::pair<edge_type, bool>      add_edge(const vertex_type& vertex_u,
                                                 const vertex_type& vertex_v,
                                                 const edge_value_type& value);
        std::pair<edge_type, bool>      add_edge(const edge_type& new_edge);

        std::pair<edge_type, bool>      remove_edge(const index_type& id);
};

template <typename VType, typename EType, std::size_t N>
graph<VType, EType, N>::graph()
{
}

template <typename VType, typename EType, std::size_t N>
graph<VType, EType, N>::~graph()
{
    my_ve_map.clear();
    my_vertices.clear();
    my_edges.clear();
}

template <typename VType, typename EType, std::size_t N>
inline const typename graph<VType, EType, N>::vertices_type& graph<VType, EType, N>::vertices() const
{
    return my_vertices;
}

template <typename VType, typename EType, std::size_t N>
inline const typename graph<VType, EType, N>::edges_type& graph<VType, EType, N>::edges() const
{
    return my_edges;
}

template <typename VType, typename EType, std::size_t N>
std::pair<typename graph<VType, EType, N>::vertex_type, bool> graph<VType, EType, N>::add_vertex(const typename graph<VType, EType, N>::vertex_value_type& value)
{
    auto new_vertex(factory::create<vertex>());

    (*new_vertex).id = my_vertices_counter.number();
    (*new_vertex).value = value;

    auto result = add_vertex(new_vertex);

    return result;
}

template <typename VType, typename EType, std::size_t N>
std::pair<typename graph<VType, EType, N>::vertex_type, bool> graph<VType, EType, N>::add_vertex(const typename graph<VType, EType, N>::vertex_type& new_vertex)
{
    auto result(std::make_pair(nullptr, false));

    return result;
}

template <typename VType, typename EType, std::size_t N>
std::pair<typename graph<VType, EType, N>::vertex_type, bool> graph<VType, EType, N>::remove_vertex(const typename graph<VType, EType, N>::index_type& id)
{
    auto result(std::make_pair(nullptr, false));

    return result;
}

template <typename VType, typename EType, std::size_t N>
std::pair<typename graph<VType, EType, N>::edge_type, bool> graph<VType, EType, N>::add_edge(const typename graph<VType, EType, N>::vertex_type& vertex_u,
                                                                                             const typename graph<VType, EType, N>::vertex_type& vertex_v,
                                                                                             const typename graph<VType, EType, N>::edge_value_type& value)
{
    auto new_edge(factory::create<edge>());

    (*new_edge).id = my_edges_counter.number();
    (*new_edge).value = value;

    (*new_edge).endpoints[0] = vertex_u;
    (*new_edge).endpoints[0] = vertex_v;

    auto result = add_edge(new_edge);

    return result;
}

template <typename VType, typename EType, std::size_t N>
std::pair<typename graph<VType, EType, N>::edge_type, bool> graph<VType, EType, N>::add_edge(const typename graph<VType, EType, N>::edge_type& new_edge)
{
    auto result(std::make_pair(nullptr, false));

    //result.first = new_edge;
    //result.second = false;

    return result;
}

template <typename VType, typename EType, std::size_t N>
std::pair<typename graph<VType, EType, N>::edge_type, bool> graph<VType, EType, N>::remove_edge(const typename graph<VType, EType, N>::index_type& id)
{
    auto result(std::make_pair(nullptr, false));

    return result;
}

END_NAMESPACE

#endif // __ALGORITHMS_GRAPH_H__
