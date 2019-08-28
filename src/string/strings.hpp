//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_STRINGS_ARRAY_H__
#define __ALGORITHMS_STRINGS_ARRAY_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename ElementType, typename Traits>
class strings : private noncopyable
{
    public:
        using traits_type = Traits;

        using element_type = ElementType;
        using elements_type = std::vector<element_type>;

        using index_type = int;
        using indices_type = std::vector<index_type>;

        using size_type = int;

        using range_type = std::pair<index_type, size_type>; // start:count
        using ranges_type = std::vector<range_type>;

    public:
        static void lrs(const elements_type& string, range_type& range);
};

template <typename ElementType, typename Traits>
inline void strings<typename ElementType, typename Traits>::lrs(const typename strings<typename ElementType, typename Traits>::elements_type& string,
                                                                typename strings<typename ElementType, typename Traits>::range_type& range)
{
    // adaptation of the https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/LongestRepeatedSubstring.java.html
    // Algorithms, 4th Edition, Robert Sedgewick and Kevin Wayne
    size_type n = static_cast<size_type>(string.size());

    range_type lrs(std::make_pair(0, 0));

    indices_type suffixes;
    std::vector<int> prefixes;

    algorithms::suffix_array<element_type, traits_type>::build(string, suffixes);
    algorithms::suffix_array<element_type, traits_type>::lcp(string, suffixes, prefixes);

    for(index_type i = 1; i < n; i++)
    {
        size_type length = prefixes[i];

        if(length >= lrs.second)
        {
            lrs = std::make_pair(suffixes[i], length);
        }
    }

    range.swap(lrs);
}

END_NAMESPACE

#endif // __ALGORITHMS_STRINGS_ARRAY_H__
