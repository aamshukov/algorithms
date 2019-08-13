//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_SORTING_INSERTION_H__
#define __ALGORITHMS_SORTING_INSERTION_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

template <typename RandomAccessIterator, typename Predicate>
class insertion : private noncopyable
{
    public:
        using iterator_type = RandomAccessIterator;
        using predicate_type = Predicate;

    public:
        static void sort(const iterator_type first, const iterator_type last, predicate_type predicate)
        {
            // https://en.wikipedia.org/wiki/Insertion_sort
            //  i ← 1
            //  while i < length(A)
            //      j ← i
            //      while j > 0 and A[j-1] > A[j]
            //          swap A[j] and A[j-1]
            //          j ← j - 1
            //      end while
            //      i ← i + 1
            //  end while
            //
            // +STL
            if(first != last)
            {
                for(auto it = first; ++it != last;) // while i < length(A)
                                                    // ++it means the first element is considered as sorted, i ← 1
                {
                    auto cur = it; // j ← i
                    auto val = std::move(*it);

                    if(predicate(val, *first))
                    {
                        // new smallest element, move to front
                        auto dst = ++cur;

                        while(first != it)
                        {
                            *--dst = std::move(*--it);
                        }

                        *first = std::move(val);
                    }
                    else
                    {
                        // looking for where to dump, must be after first as it is smallest one
                        for(auto it_loc = cur; predicate(val, *--it_loc); cur = it_loc)
                        {
                            *cur = std::move(*it_loc);
                        }

                        *cur = std::move(val);
                    }
                }
            }
        }
};

END_NAMESPACE

#endif // __ALGORITHMS_SORTING_INSERTION_H__
