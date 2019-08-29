﻿//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_GRAPH_VERTEX_H__
#define __ALGORITHMS_GRAPH_VERTEX_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename VertexValueType>
struct vertex : private noncopyable, public visitable<vertex<VertexValueType>>
{
    using vertex_value_type = VertexValueType;

    using visitor_type = visitor<vertex>;

    using index_type = int;

    index_type id = 0;
    vertex_value_type value = vertex_value_type();

    void accept(visitor_type& visitor) override;
};

template <typename VertexValueType>
void vertex<VertexValueType>::accept(typename vertex<VertexValueType>::visitor_type& visitor)
{
    visitor.visit(*this);
}

END_NAMESPACE

#endif // __ALGORITHMS_GRAPH_VERTEX_H__
