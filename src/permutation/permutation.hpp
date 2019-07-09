//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_PERMUTATION_H__
#define __ALGORITHMS_PERMUTATION_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename ElementType>
class permutation : private noncopyable
{
    public:
        using element_type = ElementType;
        using elements_type = std::vector<element_type>;

        using index_type = int;
        using indices_type = std::vector<index_type>;

        using size_type = int;

    private:
        static index_type   rank(elements_type& p, elements_type& pr, const size_type& n);

    public:
        static index_type   rank(const elements_type& permutation);
        static void         unrank(const index_type& rank, const size_type& permutation_size, elements_type& permutation);

        static index_type   rank_multiset(const elements_type& permutation);
        static void         unrank_multiset(const index_type& rank, const size_type& permutation_size, elements_type& permutation);
};

template <typename ElementType>
typename permutation<ElementType>::index_type permutation<ElementType>::rank(const typename permutation<ElementType>::elements_type& permutation)
{
    // synopsis:
    //      Wendy Myrvold, Frank Ruskey, April, 2000
    //      "Ranking and Unranking Permutations in Linear Time"
    //      wendym@csr.uvic.ca  fruskey@csr.uvic.ca
    //
    //      ALGORITHM 317 (CACM) April-May-July 1967
    //      Charles L. Robinson
    //      Institute for Computer Research, U. of Chicago, Chicago, Ill.
    size_type n = static_cast<size_type>(permutation.size());

    elements_type p(permutation.begin(), permutation.end());    // permutation
    elements_type pr(n);                                        // reverse permutation

    std::fill(pr.begin(), pr.end(), 0);

    // build reverse permutation
    for(index_type i = 0; i < n; i++)
    {
        pr[p[i]] = i;
    }

    // rank
    index_type result = rank(p, pr, n);

    return result;
}

template <typename ElementType>
typename permutation<ElementType>::index_type permutation<ElementType>::rank(typename permutation<ElementType>::elements_type& p,
                                                                             typename permutation<ElementType>::elements_type& pr,
                                                                             const typename permutation<ElementType>::size_type& n)
{
    if(n == 1)
    {
        return 0;
    }

    index_type s = p[n - 1];

    std::swap(p[n - 1], p[pr[n - 1]]);
    std::swap(pr[s], pr[n - 1]);

    return s + n * rank(p, pr, n - 1);
}

template <typename ElementType>
void permutation<ElementType>::unrank(const typename permutation<ElementType>::index_type& rank,
                                      const typename permutation<ElementType>::size_type& permutation_size,
                                      typename permutation<ElementType>::elements_type& permutation)
{
    index_type r = rank;
    size_type n = permutation_size;

    elements_type& p(permutation);

    p.resize(n);

    std::fill(p.begin(), p.end(), 0);

    // build identity permutation
    for(index_type i = 0; i < n; i++)
    {
        p[i] = i;
    }

    // unrank
    while(n > 0)
    {
        std::swap(p[n - 1], p[r % n]);

        r /= n;
        n--;
    }
}

template <typename ElementType>
typename permutation<ElementType>::index_type permutation<ElementType>::rank_multiset(const typename permutation<ElementType>::elements_type& permutation)
{
    return 0;
}

template <typename ElementType>
void permutation<ElementType>::unrank_multiset(const typename permutation<ElementType>::index_type& rank,
                                               const typename permutation<ElementType>::size_type& permutation_size,
                                               typename permutation<ElementType>::elements_type& permutation)
{
}
END_NAMESPACE

#endif // __ALGORITHMS_PERMUTATION_H__
