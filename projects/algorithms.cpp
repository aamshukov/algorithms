#include <core/pch.hpp>
#include <core/noncopyable.hpp>

#include <suffixarray/suffixarray.hpp>
#include <permutation/permutation.hpp>

USINGNAMESPACE(algorithms)

void test_suffix_array();
void test_permutation();

int main()
{
    test_permutation();
    test_suffix_array();
}

void test_suffix_array()
{
    string_type str(L"cabbage");

    std::vector<char_type> s(str.begin(), str.end());
    s.push_back(0); // add virtual sentinel

    struct sa_traits
    {
        static int abc_size()
        {
            return 255;
        }
    };

    using traits_type = sa_traits;

    const int count = 1;

    {
        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < count; i++)
        {
            std::vector<int> naive_sa;
            suffix_array<char_type, traits_type>::build(s, naive_sa, suffix_array<char_type, traits_type>::algorithm::naive);
            suffix_array<char_type, traits_type>::print(s, naive_sa);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        std::wcout << std::endl << L"Naive time is " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;
    }

    std::cout << std::endl;

    {
        auto start = std::chrono::high_resolution_clock::now();

        for(int i = 0; i < count; i++)
        {
            std::vector<int> sa_is;

            suffix_array<char_type, traits_type>::build(s, sa_is);
            suffix_array<char_type, traits_type>::print(s, sa_is);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        std::wcout << std::endl << L"SA-IS time is " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;
    }
}

void test_permutation()
{
    using permutation_type = permutation<int>;
    
    permutation_type::elements_type permutation;

    permutation.emplace_back(3);
    permutation.emplace_back(6);
    permutation.emplace_back(1);
    permutation.emplace_back(2);
    permutation.emplace_back(5);
    permutation.emplace_back(4);
    permutation.emplace_back(7);
    permutation.emplace_back(0);

    for(permutation_type::index_type k = 0; k < 1000; k++)
        std::next_permutation(permutation.begin(), permutation.end());

    permutation_type::index_type rank = permutation_type::rank(permutation);
    std::cout << rank << std::endl;

    permutation_type::elements_type permutation2;
    permutation_type::unrank(rank, (permutation_type::size_type)permutation.size(), permutation2);

    for(auto element : permutation)
    {
        std::wcout << char_type(element + 49) << L' ';
    }
    std::wcout << std::endl;

    for(auto element : permutation2)
    {
        std::wcout << char_type(element + 49) << L' ';
    }
    std::wcout << std::endl;
}
