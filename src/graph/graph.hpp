//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_GRAPH_H__
#define __ALGORITHMS_GRAPH_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename ElementType>
class graph : private noncopyable
{
    public:
        using element_type = ElementType;
        using elements_type = std::vector<element_type>;

        using index_type = int;
        using indices_type = std::vector<index_type>;

        using size_type = int;
};

END_NAMESPACE

#endif // __ALGORITHMS_GRAPH_H__
