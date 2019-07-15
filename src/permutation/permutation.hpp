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

        using multiset_element_type = int;
        using multiset_elements_type = std::vector<multiset_element_type>;;

        using index_type = int;
        using indices_type = std::vector<index_type>;

        using size_type = int;
        using rank_type = std::size_t;

    private:
        static rank_type    rank(elements_type& p, elements_type& pr, const size_type& n);

    public:
        static rank_type    rank(const elements_type& permutation);
        static void         unrank(const rank_type& rank, const size_type& permutation_size, elements_type& permutation);

        static rank_type    rank_multiset(const elements_type& multiset, const multiset_elements_type& multiset_domain);
        static void         unrank_multiset(const rank_type& rank,
                                            const multiset_elements_type& multiset_domain,
                                            const size_type multiset_size,
                                            elements_type& multiset);
};

template <typename ElementType>
typename permutation<ElementType>::rank_type permutation<ElementType>::rank(const typename permutation<ElementType>::elements_type& permutation)
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
    rank_type result = rank(p, pr, n);

    return result;
}

template <typename ElementType>
typename permutation<ElementType>::rank_type permutation<ElementType>::rank(typename permutation<ElementType>::elements_type& p,
                                                                            typename permutation<ElementType>::elements_type& pr,
                                                                            const typename permutation<ElementType>::size_type& n)
{
    if(n == 1)
    {
        return 0;
    }

    rank_type s = p[n - 1];

    std::swap(p[n - 1], p[pr[n - 1]]);
    std::swap(pr[s], pr[n - 1]);

    return s + n * rank(p, pr, n - 1);
}

template <typename ElementType>
void permutation<ElementType>::unrank(const typename permutation<ElementType>::rank_type& rank,
                                      const typename permutation<ElementType>::size_type& permutation_size,
                                      typename permutation<ElementType>::elements_type& permutation)
{
    rank_type r = rank;
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
typename permutation<ElementType>::rank_type permutation<ElementType>::rank_multiset(const typename permutation<ElementType>::elements_type& multiset,
                                                                                     const typename permutation<ElementType>::multiset_elements_type& multiset_domain)
{
    // multiset_domain must be zero based
    rank_type result = 0; // rank

    index_type position = 1; // weighted position

    size_type multiset_size = static_cast<size_type>(multiset.size());
    size_type multiset_domain_size = static_cast<size_type>(multiset_domain.size());

    for(index_type i = 0; i < multiset_size; i++)
    {
        index_type index = multiset_size - i - 1;

        result += position * multiset_domain[multiset[index]];

        position *= multiset_domain_size;
    }

    return result;
}

template <typename ElementType>
void permutation<ElementType>::unrank_multiset(const typename permutation<ElementType>::rank_type& rank,
                                               const typename permutation<ElementType>::multiset_elements_type& multiset_domain,
                                               const typename permutation<ElementType>::size_type multiset_size,
                                               typename permutation<ElementType>::elements_type& multiset)
{
    // multiset_domain must be zero based
    rank_type rank0 = rank;

    multiset.resize(multiset_size);

    std::fill(multiset.begin(), multiset.end(), 0);

    size_type multiset_domain_size = static_cast<size_type>(multiset_domain.size());

    size_type multiplication_step = multiset_domain_size;

    auto position = static_cast<std::size_t>(std::pow(multiplication_step, multiset_size)); // max weighted position

    for(index_type i = 0; i < multiset_size; i++)
    {
        position /= multiplication_step;

        index_type index = static_cast<index_type>(rank0 / position);

        multiset[i] = multiset_domain[index];

        rank0 %= position;
    }
}

END_NAMESPACE

#endif // __ALGORITHMS_PERMUTATION_H__
