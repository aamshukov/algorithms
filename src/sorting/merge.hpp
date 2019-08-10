//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_SORTING_MERGE_H__
#define __ALGORITHMS_SORTING_MERGE_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename RandomAccessIterator, typename Predicate>
class merge : private noncopyable
{
    public:
        using iterator_type = RandomAccessIterator;
        using element_type = typename iterator_type::value_type;
        using container_type = std::vector<element_type>;

        using predicate_type = Predicate;

        using index_type = int;
        using size_type = int;

    public:
        static void sort(const iterator_type first, const iterator_type last, predicate_type predicate)
        {
            // https://www.algorithmist.com/index.php/Merge_sort
            // https://algs4.cs.princeton.edu/22mergesort/MergeBU.java.html
            size_type n = static_cast<size_type>(std::distance(first, last));

            container_type aux(n); // O(n) space

            size_type m = 1; // run size - split in runs of 1, 2, 4, 8, ..., 2^m in size

            while(m < n)
            {
                //std::wcout << m << std::endl;

                index_type i = 0;

                while(i < n - m)
                {
                    // calculate left and right runs' coordinates
                    index_type left_run_start = i;
                    index_type left_run_end = i + m -1;

                    index_type right_run_start = i + m;
                    index_type right_run_end = std::min(i + 2 * m - 1, n - 1);

                    //std::wcout << left_run_start << L"," << left_run_end << L"  " << right_run_start << L',' << right_run_end << std::endl;

                    // merge runs a[i .. i+m-1] and a[i+m .. min(i+2*m-1, n-1)]
                    {
                        auto curr(first);

                        std::advance(curr, left_run_start);

                        for(index_type k = left_run_start; k <= right_run_end; k++)
                        {
                            aux[k] = std::move(*curr);
                            std::advance(curr, 1);
                        }

                        index_type i = left_run_start;
                        index_type j = right_run_start;

                        auto dest(first);

                        std::advance(dest, left_run_start);

                        for(index_type k = left_run_start; k <= right_run_end; k++)
                        {
                            if(i > right_run_start - 1) // i > mid
                                *dest = std::move(aux[j++]);
                            else if(j > right_run_end)
                                *dest = std::move(aux[i++]);
                            else if(predicate(aux[j], aux[i]))
                                *dest = std::move(aux[j++]);
                            else
                                *dest = std::move(aux[i++]);

                            std::advance(dest, 1);
                        }
                    }

                    i = i + 2 * m;
                }

                m = m * 2;
            }
        }
};

END_NAMESPACE

#endif // __ALGORITHMS_SORTING_MERGE_H__
