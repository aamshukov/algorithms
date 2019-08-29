//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_GRAPH__ALGORITHM_H__
#define __ALGORITHMS_GRAPH__ALGORITHM_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename GraphType>
class graph_algorithm : private noncopyable
{
    public:
        using graph_type = std::shared_ptr<GraphType>;
        using visitor_type = typename GraphType::visitor_type;

        enum class color
        {
            white = 0,  // not processed
            grey,       // processed
            black       // processed with kids
        };

    public:
        static void                     dfs(const graph_type& g, const visitor_type& visitor);

        static bool                     has_cycle(const graph_type& g);
};

template <typename GraphType>
void graph_algorithm<GraphType>::dfs(const typename graph_algorithm<GraphType>::graph_type& g, const typename graph_algorithm<GraphType>::visitor_type& visitor)
{
}

template <typename GraphType>
bool graph_algorithm<GraphType>::has_cycle(const graph_algorithm<GraphType>::graph_type& g)
{
    bool result = false;

    return result;
}

END_NAMESPACE

#endif // __ALGORITHMS_GRAPH__ALGORITHM_H__
