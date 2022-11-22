//..............................
// UI Lab Inc. Arthur Amshukov .
//..............................
#ifndef __ALGORITHMS_MISC_ARRAY_H__
#define __ALGORITHMS_MISC_ARRAY_H__

#pragma once

BEGIN_NAMESPACE(algorithms)

class misc : private noncopyable
{
    public:
        template <typename ElementType, typename SizeType = int>
        static void zigzag(const std::vector<ElementType>& matrix2d, SizeType rows, SizeType colsrows, std::vector<ElementType>& result_data);
};

template <typename ElementType, typename SizeType>
inline void misc::zigzag(const std::vector<ElementType>& matrix2d, SizeType rows, SizeType cols, std::vector<ElementType>& result_data)
{
    // adaptation of the https://www.hackingnote.com/en/interview/problems/matrix-zigzag-traversal
    using element_type = ElementType;
    using elements_type = std::vector<element_type>;

    using size_type = SizeType;

    using index_type = size_type;
    using indices_type = std::vector<index_type>;

    if(!matrix2d.empty())
    {
        elements_type result(matrix2d.size());

        auto n = rows + cols - 1; // ... rows + cols - 1 linear scans

        for(index_type i = 0, k = 0; i < n; i++)
        {
            if(i % 2 == 1) // ... odd scans are going down-left
            {
                int r = i < cols ? 0 : i - cols + 1;
                int c = i < cols ? i : cols - 1;

                while(r < rows && c >= 0) // ... keep moving until we reach the edge of the matrix
                {
                    result[k++] = matrix2d[cols * r + c];
                    r++;
                    c--;
                }
            }
            else // ... even scans are going up-right
            {
                int r = i < rows ? i : rows - 1;
                int c = i < rows ? 0 : i - rows + 1;

                while(r >= 0 && c < cols) // ... keep moving util we reach the edge of the matrix
                {
                    result[k++] = matrix2d[cols * r + c];
                    r--;
                    c++;
                }
            }
        }

        result_data.swap(result);
    }
}

END_NAMESPACE

#endif // __ALGORITHMS_MISC_ARRAY_H__
