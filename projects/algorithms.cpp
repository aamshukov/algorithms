#include <core/pch.hpp>
#include <core/noncopyable.hpp>
#include <core/factory.hpp>
#include <core/counter.hpp>
#include <core/enumerate.hpp>

#include <core/visitor.hpp>
#include <core/visitable.hpp>

#include <suffixarray/suffixarray.hpp>
#include <permutation/permutation.hpp>
#include <permutation/permutation_entropy.hpp>

#include <string/strings.hpp>

#include <sorting/merge.hpp>
#include <sorting/insertion.hpp>

#include <sorting/topological.hpp>

#include <iprecision.h>

#include <misc/misc.hpp>


USINGNAMESPACE(algorithms)

void test_suffix_array();
void test_permutation();
void test_permutation256();
void test_strings();
void test_merge_sort();
void test_insertion_sort();
void test_permutation_entropy();
void test_zigzag();

//unsigned long int hi;
//
//void deeplynested()
//{
//    unsigned long int lo, len;
//    lo = (unsigned int) &lo;
//    len = hi - lo;
//    len /= 1024;
//    len /= 1024;
//}

//void check_stack_size(int level)
//{
//    byte frame[1024 * 1024 * 1024];
//    frame[0] = 0;
//    uint64_t s = level * 1024 * 1024 * 1024;
//    std::cout << s << std::endl;
//    check_stack_size(level + 1);
//}

void log(const std::string_view message, const std::source_location location = std::source_location::current())
{
    std::clog << "file: "
              << location.file_name() << "("
              << location.line() << ":"
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
}
 
template <typename T> void fun(T x)
{
    log(x);
}
 
 class Abc
 {
    public:
        void foo()
        {
            log("from class");
        }
 };

int main()
{
    log("Hello world!");
    fun("Hello C++20!");

    Abc abc;
    abc.foo();

    //check_stack_size(1);

    //int mainvar;
    //hi = (unsigned long int) &mainvar;
    //deeplynested();

    //test_zigzag();
    //test_permutation256();
    test_suffix_array();
    test_permutation();
    test_permutation_entropy();
    test_insertion_sort();
    test_merge_sort();
    test_strings();
}

void test_strings()
{
    struct sa_traits
    {
        static int abc_size()
        {
            return 255;
        }
    };

    using traits_type = sa_traits;

    using strings_type = strings<char_type,traits_type>;

    //string_type str(L"ABRACADABRA");
    //string_type str(L"0011101010001101110011001110101001111100001011000101101010011011011010010100110001100101001010111001011011010001100101010000110110100001001100110110001111111010010110010101110011101001010110101101111100011001010010111010101000001111011000011100110101101100010100100111100101001011111100001011001011010101011000101111000111111100001011100001110010111001010111101010001111010011001010100001011100110011001010110001000110101100100101100010001010110101110110001100100011101100101100011010110001101101011011000010110101110011101000111010000111101101000011011110101011010011110001110110010100110110011010001101100100101110000011100101111011010100110100111011100110110001001001111100011100111001110001010010011110001010010101100011010000110011001011010101001100111011010101010110010111010011001001101000111000011100010110110101100011011000111000010011001111000000101100001101100011010011101001110100001110001101100011111000001100010001111001110011001001010011100101101100010010011110011001011000110010010011111010011011001000111001110011110010111000010001110011010001100101101010010111101100010001111010101001101100011010101110100010111010011000011000011100011010010011110001011010101010011011110011110000010011001101000111100110001111100000011100001101101110011100100100011100101110010100010011011101010110010111100101110011101001101001000101101010011101010101001101100111011010101011011100010010101001110111010000001101101100010110101010011010110110110000011001001111001100110101101100001111010010001111100111010000110010101010001111000011010101101010110001101010001110001101101101101000010101010100010101110011010111010100101001001010110111001011010110100011101001100011011001111100011101100011010111010100001110101010111010010011011100110101100111110000111100000111101001110011011010100100110001001101010111001110000001011110110000100101011110000011100011110101000111110001010011001111011100100110011010101111010001110100010011111110001000110101101010001101010100001011101100101101001011001000011010001101100010100110101101001011010010011010101110000011110101011100011000101101111001001101111100000110111001101001010100111011010101011010010110001011100011010010100110010101001110000111101000101001001110011010010011010010110011001100110100111010111000100110000110101001101010011010010110100100011011001101011001100011110001010110100101010011111000110101000110110001001101011000100101101011010011101110001100111010110101110010110101000110111100101011100001100100011110100111011010101001100010011110101010110001001101110010100110011110101011100000011100101100101010010101001000101100001110011110100101000101101101001110100100101100100110101100110011001100101001011000010111001110111010001000111100001110011010001010010111100111011100010110100011101000111101101100001100100111000111001010101001100110010101111001011000101000011001001100111101000101100110000111101100101011100110100010010111101100000010111010100011001000110110011100111000001100101010001101001010010010001011100110010001110111100001010111010010111100111010001110001000101010111011001000111010001110110011010011010100110110110010110110010101110001101000101011001011000101010001100011100101010110010001101101110001001100100111010110000000111110110011001000110101010001110011001001100110000110011100100011000110101011000110011101011001000111000101011010100110100100110110100111000111110100011010101001010101001011010110100010100101000011111000010110100011001100100111100110001010101000110001101011000100011101110010110100111101001100001100010111101000110011011000110001101101010010110000100111010101001101110010101010100001011010110011100011101000111000101011001001011000101110101100010010101011001101001001101011011000011101100110000101111101100001100101101001100001010100111011001110100010110001000110110011100011010101000011011110001000011110001011000011101010110110010011010101001011100011011000101101100010110010011000011010001110101001100111011001100010111010000111010010110010010001010100011001100101101011001101101011001110010110001101100101011011100101001111010101000011001100111000101011001110001001110110011100101011010010100100011010001001110001011010001010101001101100101110001110001001011001001001110011100000100111010010110101101001010101000100011010011101011001000101010011010110001010100010011110110110001110000110100100011010010011110000100100101010010001101010111010010100011110010011111001010010101111001001010100010011000111111101001010101010111001101101100100010010110110011010001111001001010110011010001101101101010100110000101101101010000111101101011110001110001001110101111001100010101010110111000010110001111011000011011001110000111010101010011101010011001010011110100011010100100000111011001111100010011110011001000001110101011100001110100110001110110000110100101001001011000111001100101100010101000101111100001011100000101010100101111010001010010011110001111011100001001011100100110010010011011101010110011000111100101001111110000111001011010111110000001111110011000011101001011010010111110000100110011001011100000110101111100001011000001011011101010010011100010101010100101011010001010110101010100101010100011010010110111010011011010010011001001110010101101101000101010101101110100110100010100101110011001110011001110100111100110110101000101010001111101100011000111001001001101101110011001011101100001001010111000011010001100100010110001001110011001001100110100011000111010110001100100100110011010101100001001010001011001100101010100010101111000101011011011100101101000010111101000110001110001110111001101011000111011100110010010111011001011100100011100100111110010110011010110010101100001100101010010110100100011101011101101001001101001100110001111101001101010100010111100011100111001101000011101000010110001011001101110111001101010101001000011011001011010001110110001111000001101111010010011011001101101110101010011110001101101000011101100101101101100101011100111010101000111010010101001100010110010110001101110101100110100110001011101001110010100101000110101101101110001001100011101000101110101010001110110011000010111100010010110100011110011101110000110000110110101101010101101010010111111001010110010110101100110101110010110011000011101011100011110101100110000111101010110001110010110110011111001000101010111010101100111000100110101000011101110001001011100110110110010011100000111001101011001100010111000101100101001010111001100110000111110001110011010100101101100101000111010001101001011110001011000110010011110000011101000110111010101000011111010001100101101000010101010001110001110100101001001110010110011100011001011111000001011010011101110100100011010011011011000011110001110000010011001111011000101101100111000011010001000011011010110011001011000001111011001100101001001100101101001011001110000110110011011000110100110101011100110011010101110100101101010011101101101100100010111000110011111000101110001101100001011001101011010010100110101011001110010101011010111001111001110100110110011011001011001001110000110111010011100010110110000011101000111110100100010111110110001000111100001100011110010110110001111001000110010011010011001100111010001111111001010101101100010100101101010110110010111100010101101001100010101010100101010110011110000100111100110111001000110101010011011100111000011001100111000010010101011010101011011100000100111010010101111001010010111100000111000001111010011010");
    string_type str(L"23424132214321233132212413414343232113241324411341422113214312322414134331433214232321432413312334312413241231141321131412211314244212142321143241243442232134342423124114143124234321242314124312213441311341311313122143433423213431122432121421133224132332344134313443431424322112231234342123324124422434234232214123123132413414424312434124144213131443134114132441141424424234211241141431233231434223132342143413424312234214241331211323321343344114234221122321143231413121231314341231423234324241421434242421122132242332312132144123413221421424131431344323424334434342312341211424142312312321344231424234233241243123423123422312344223143432141313241414121212131434412413411324423434143131421413432342134213134331242134231421212414321434134214323432432412132324122324124234122313241324212343142421343124212113421224121431341232232331233442241241141432341321312343214323234123142124434242211231124343131221231423211442344231233243122132324332422442342413124123131321244142344242313441414312312423344342211212142113413113144142414214122112313414143243433113242143131321321442312134434114234131421442213243311221413141423142212114322334434124323231241314411241432112212413213232233134433134144343141241422414142443142431134123231434243131231242311313414132213212121313134114244331143212233214422423323132311413433232241343433214232113231214323213241342313214243431242123321424421424212121132312431331414232231343313432144332123113134124231234234314342441341341324141343143323232312123311323434114343113432423142431144114233213121213143423424141413212411213131224341234131224143423142324243142212342242123311234343234432143313413411231132123134241231321143124124232431431321231242432424241211223321434411242124342122341312124242334133214322114123242431212241212242143321224422414133221122443343243243113423213212124214313312113124334142132214121144141124243133143422114342332431441314341341232132332241242323132243421342424313134124223424141232131322431321432321312141341243142231314233232311312212313213223314314321312311323423424423124212443214341423132233114141231321231422131322341422314343231342434322434424232143441433124134132421213433123234343414221343132212142123232234131214321213124133432241223344123431242434313422441431243313412123121421324244113421214134113143241122141142134213413323142142112424234434132131423141342422123312142133423211423122343314332343221423221213223434242324241323242212412143412134212214224431421231413344134344241231324314232323212434331243434121243242132124313323234321221214213133424423213231423433431414143132124344121121423342132132434431431142113344231232334141412314112343134132331312323434224121324421434232314341313243124323214314223432123211243321332242142241442144312133114344342422421311342434121211213243112244121414114433221241224324241243243434314213423322123234312341331143143122434412134122142213114343123343431344143432312243442314123423431341443134324244231123431124242421243133223122413244241234334434324213414122313134232424113321243432432231234413431141443343231143142132343344213424121232334412341424131412441231234323243214143412112313414312141144221134143134142411232133241242113341342311314244214233424132314411221213232121313122324421442133243211332343442123224431314124223213141243142241434323223434124234321132142233114143141414114121234234112232432144314341224411242241441144242421332213214431414122442144131123424242341133141241332344232141341244221413124141443244121342441434213124241411421212421241313342123423243131312313231121413413114414241214334424124431232321312431424342142342432213121313112344214213114422324121234312114142432341431323143423124342141434332124221342114124121433114213232423123421343211243243143311232213231124324343131344341323434311223321414212313142124323132123232414131424214321324413143421231244221243132231323234141314112132421123232411432433241311434422423143212213414413413132334142432421231322131143421324212244341141214241243431334143442423124411223411314122412212143133142234121324224134224131231123124311434343134342113242113421224341421412314421214234331131424421343341431123121244131241413214223412112343234311423312313342324144121241412311231213223143214234224141431133424133242122421122431423212422323323414432134313123342123243224234221314123134314232132412143234223414131343243144243233223131431144134341324323412324131244121141232132321321412134213242142212332422132433414321413342424314224231331211343131232143232344234341243432423412413232412411412324132213123134112321331312113322441214134344234421234243221231241234142432323314121241341122121423132131314431221143124413221424334412132232112432323241412343221344114321434433412344243422134231334341414241441121242421231211313213232432331422413241331124324311213134232321413243414423424311312213442342313434323341424314332343231121334312113243113411342434342123421231334234324242421214323123431421424212441432341142324323131414312121224121443142432324212233112414212313123421313322142424313231331424313432334243113142124411223411224244142323141421441232323344221323221142432212334244212231414421243213134212114432314231242322442413224423223322413312343432314323241433213241321313114434134143413234243122442214223124241121323413423143143142324121332143124412343213434432114411331431234211314322132314142413142244312424243422142344142132132244143141321124323344114131334343234123443214342234332434332421331232432413232212441313421212343424141232421124242322331142112312323214224413421233223343442341423123113121343212121231321131242243431124321211342413232213113431241432441424312343441312321233124314314231413142323244331121341411431324123434342233412144224231424424232233421414334312143122323421443233434144124134121421432211212134121343243123132243441134241322134413124421412122341214343143421344112214131243141242313312442244143411242232143422124132141244343244323121432243242422134343431314312143441122432313442144143233114313234144113343413214232413421142324311331434112422413321341421224214321131314132413342114242112211334211324133224342314341213211441121213414124141234231212233112431224233421133142314113314241434214311421312412324334243131214343243112143434412123244321134321124331422121432113344131343142244221424323214224123241342314424324434321312131231242411332123214421442231224142131322312211343242414121421213121414141424234343131324131212423123413243224343423321213131323213243421421144343141441141423232141411223122342122331411342414143324341124343121332122313232142431341424231231323134234323432314231212423214113321442131213311432423142131223133224212423134324144214323221322331423232211421242134141314422143142442241241431334312441411441414114143414431412342112322132233113314143234341241212314143313413343143134143122334143431213112231442244241432314322312243421414241434112412421324332231221134132324323414143431334243423234142433143142432413224414243241443433223433243");

    std::wcout << str << L":" << str.size() << std::endl;

    string_type substr;

    int total = 0;

    for(;;)
    {
        //std::wcout << str << L":" << str.size() << std::endl;

        std::vector<char_type> s(str.begin(), str.end());
        s.push_back(0); // add virtual sentinel

        strings_type::range_type range;

        strings_type::lrs(s, range);

        if(substr.empty() && str.size() > range.second)
        {
            substr = str.substr(range.first, range.second);
            //std::wcout << substr << L":" << range.first << std::endl;
        }

        if(substr.empty())
        {
            break;
        }

        //std::wcout << range.first << L":" << range.second << std::endl;
        //std::wcout << substr << std::endl;

again:
        auto k = 0;

        auto offset = str.find(substr, 0);

        while(offset != std::string::npos)
        {
            //std::wcout << substr << L":" << offset << std::endl;
            offset = str.find(substr, offset + substr.size());
            k++;
        }

        if(k <= 1)
        {
            substr.erase(substr.size() - 1, 1);

            if(substr.size() >= 8)
            {
                goto again;
            }
        }

        offset = str.find(substr, 0);

        while(offset != std::string::npos)
        {
            std::wcout << substr << L":" << offset << L":" << str.size() << std::endl;
            str.erase(offset, substr.size());
            offset = str.find(substr, offset);
            total++;
        }

        if(substr.size() < 8)
        {
            substr.clear();
        }

        if(str.size() < 32)
        {
            break;
        }
    }

    std::wcout << str << L":" << str.size() << std::endl;
}

void test_suffix_array()
{
    string_type str(L"cabbage");
    //string_type str(L"banana");
    //string_type str(L"ABRACADABRA");
    //string_type str(L"rikki-tikki-tikka");
    //string_type str(L"baabaabac");

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
            std::vector<int> prefixes;

            suffix_array<char_type, traits_type>::build(s, naive_sa, suffix_array<char_type, traits_type>::algorithm::naive);
            suffix_array<char_type, traits_type>::print(s, naive_sa, prefixes);
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
            std::vector<int> suffixes;
            std::vector<int> prefixes;

            suffix_array<char_type, traits_type>::build(s, suffixes);
            suffix_array<char_type, traits_type>::lcp(s, suffixes, prefixes);
            suffix_array<char_type, traits_type>::print(s, suffixes, prefixes);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

        std::wcout << std::endl << L"SA-IS time is " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;
    }
}

void test_permutation()
{
    using permutation_type = permutation<int, int_precision>;
    
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

    permutation_type::rank_type rank = permutation_type::rank(permutation);
    std::cout << rank << std::endl;

    permutation_type::elements_type permutation2;
    permutation_type::unrank(rank, (permutation_type::size_type)permutation.size(), permutation2);

    for(auto element : permutation)
    {
        std::wcout << char_type(element + 48) << L' ';
    }
    std::wcout << std::endl;

    for(auto element : permutation2)
    {
        std::wcout << char_type(element + 48) << L' ';
    }
    std::wcout << std::endl;

    //permutation_type::multiset_elements_type multiset = { 0, 0, 0, 1, 1, 2, 2, 0, 0, 0, 1, 1, 2, 2 }; // 1474650
    //permutation_type::multiset_elements_type multiset_domain = { 0, 1, 2, 3};

    permutation_type::multiset_elements_type multiset = { 1, 2, 3, 1, 3, 0, 2, 1, 1, 0, 3, 2, 1, 0, 1, 2 }; // 1841909318
    permutation_type::multiset_elements_type multiset_domain = { 0, 1, 2, 3 };

    permutation_type::rank_type multiset_rank = permutation_type::rank_multiset(multiset, multiset_domain);

    std::cout << multiset_rank.toString() << std::endl;

    permutation_type::multiset_elements_type multiset0;

    permutation_type::unrank_multiset(multiset_rank, multiset_domain, static_cast<permutation_type::size_type>(multiset.size()), multiset0);

    std::wcout << (multiset == multiset0) << std::endl;

    auto count = 0; //std::numeric_limits<permutation_type::rank_type>::max() - 1;

    for(auto i = 0; i < count; i++)
    {
        permutation_type::multiset_elements_type ms;
        
        permutation_type::unrank_multiset(i, multiset_domain, 16, ms);
        permutation_type::rank_type ms_rank = permutation_type::rank_multiset(ms, multiset_domain);

        for(auto element : ms)
        {
            std::wcout << char_type(element + 48) << L' ';
        }

        std::wcout << std::endl;

        if(ms_rank != i)
        {
            std::wcout << L"Zopa: " << i << std::endl;
            break;
        }
    }

    //permutation_type::multiset_elements_type ms { 3, 4, 5, 1, 1, 2 };
    permutation_type::multiset_elements_type ms { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };

    std::vector<permutation_type::elements_type> permutations;

    {
        auto start = std::chrono::high_resolution_clock::now();
        permutation_type::generate_multiset_permutation(ms, permutations);
        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::wcout << std::endl << L"generate_multiset_permutation " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;
        std::wcout << permutations.size() << std::endl;
    }

    for(auto permutation : permutations)
    {
        for(auto element : permutation)
        {
            std::wcout << char_type(element + 48) << L' ';
        }

        std::wcout << std::endl;
    }

    std::size_t k = 0;

    {
        auto start = std::chrono::high_resolution_clock::now();
        for(auto multiset : permutation_type::generate_multiset_permutation_lazy(ms))
        {
            if(permutations[k++] != multiset)
            {
                std::wcout << L"zopa" << std::endl;
                break;
            }

            //for(auto element : multiset)
            //{
            //    std::wcout << char_type(element + 48) << L' ';
            //}

            //std::wcout << std::endl;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        std::wcout << std::endl << L"generate_multiset_permutation_lazy " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;
    }

    std::wcout << k << std::endl;
}

void test_permutation256()
{
    using permutation_type = permutation<int, int_precision>;

    permutation_type::rank_type rank = int_precision("15768436584365387658715768436584365387658765298478273274247225362545711130183921399758598437594375346793857943875759365934524029482048325798433947529402840928409387658765298478273274247225362545711130183921399");
    permutation_type::size_type size = 256;

    permutation_type::elements_type permutation;

    permutation_type::unrank(rank, size, permutation);

    for(auto element : permutation)
    {
        std::wcout << std::to_wstring(element) << L' ';
    }

    std::wcout << std::endl << std::endl;

    using slice_type = std::vector<int8_t>;
    using slices_type = std::vector<slice_type>;

    slices_type slices;
    permutation_type::elements_type positions;

    for(auto k = 15; k >= 0; k--)
    {
        // build slice
        slice_type slice(size, false);
        permutation_type::elements_type positions0;

        for(auto j = 0; j < size; j++)
        {
            auto lb = k * 16; // low bound
            auto hb = lb + 16; // high bound

            auto el = permutation[j];

            if(el >= lb && el < hb)
            {
                slice[j] = 1;
                positions0.emplace_back(j);
            }
        }

        std::wstringstream stream;

        //for(auto element : slice)
        //{
        //    stream << std::to_wstring(element);
        //}
        //stream << L":" << std::to_wstring(slice.size());

        //std::cout.clear();

        if(!positions.empty())
        {
            // mark elements to be deleted
            for(auto position : positions)
            {
                slice[position] = 2;
            }

            auto it(slice.begin());

            while(it != slice.end())
            {
                if(*it == 2)
                {
                    it = slice.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        if(slice[slice.size() - 1] == 0) // last 0s are not significant!!!
        {
            auto it = std::find(slice.rbegin(), slice.rend(), 1) + 1;
            auto sz = slice.rend() - it + 1;
            slice.resize(sz);
        }

        slices.emplace_back(slice);

        for(auto element : slice)
        {
            stream << std::to_wstring(element);
        }
        stream << L":" << std::to_wstring(slice.size()) << std::endl;

        positions.insert(positions.end(), positions0.begin(), positions0.end());

        stream.flush();

        std::wcout << stream.str();
    }

    std::size_t total = 0;
    for(auto& slice : slices)
    {
        total += slice.size();
    }

    std::wcout << total << std::endl;
}

void test_merge_sort()
{
    using container_type = std::vector<int>;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    auto count = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    while(count > 0)
    {
        if(count % 1000 == 0)
            std::wcout << count << std::endl;

        count--;

        std::vector<int> elements;

        for(int k = 0; k < count; k++)
        {
            elements.emplace_back(std::rand());
        }

        merge<container_type::iterator, std::less<int>>::sort(elements.begin(), elements.end(), std::less<int>());
        //merge<container_type::iterator, std::less<int>>::sort(++elements.begin(), --elements.end(), std::less<int>());

        if(!std::is_sorted(elements.begin(), elements.end()))
        {
            std::wcout << L"ERROR!!!";
        }
        else
        {
            //for(auto element : elements)
            //{
            //    std::wcout << element << L' ';
            //}
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::wcout << std::endl << L"Time is " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;

    std::wcout << std::endl;
}

void test_insertion_sort()
{
    using container_type = std::vector<int>;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    auto count = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    while(count > 0)
    {
        if(count % 1000 == 0)
            std::wcout << count << std::endl;

        count--;

        std::vector<int> elements;

        for(int k = 0; k < count; k++)
        {
            elements.emplace_back(std::rand());
        }

        insertion<container_type::iterator, std::less<int>>::sort(elements.begin(), elements.end(), std::less<int>());

        if(!std::is_sorted(elements.begin(), elements.end()))
        {
            std::wcout << L"ERROR!!!";
        }
        else
        {
            //for(auto element : elements)
            //{
            //    std::wcout << element << L' ';
            //}
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::wcout << std::endl << L"Time is " << milliseconds.count() << L"(ms), " << seconds.count() << L"(s)" << std::endl;


    std::wcout << std::endl;
}

void test_permutation_entropy()
{
    using element_type = permutation_entropy<>::element_type;
    using elements_type = permutation_entropy<>::elements_type;
    using matrix_type = permutation_entropy<>::matrix_type;
    using index_type = permutation_entropy<>::index_type;

    matrix_type state_space;

    elements_type ts = { 4, 7, 9, 10, 6, 11, 3 };

    auto dimension = 3;
    auto delay = 1;

    permutation_entropy<>::partition_state_space(ts, dimension, delay, state_space);

    for(auto [k, v] : enumerate(state_space))
    {
        if((k % dimension) == 0)
        {
            std::wcout << std::endl;
        }

        std::wcout << v << L' ';
    }

    std::wcout << std::endl << std::endl;

    byte key = 0;

    #define calc_key(x, y, z, v)    \
        v = 0;                      \
        v |= (x << 4) & 0x3f;       \
        v |= (y << 2) & 0x3f;       \
        v |= (z << 0) & 0x3f;

    std::unordered_map<element_type, index_type> pm;

    calc_key(0, 1, 2, key)
    pm[key] = 0;
    calc_key(0, 2, 1, key)
    pm[key] = 1;
    calc_key(1, 0, 2, key)
    pm[key] = 2;
    calc_key(1, 2, 0, key)
    pm[key] = 3;
    calc_key(2, 0, 1, key)
    pm[key] = 4;
    calc_key(2, 1, 0, key)
    pm[key] = 5;

    using permutation_type = permutation<int>;

    auto count = 40320;

    for(int k = 0; k < count; k++)
    {
        permutation_type::elements_type permutation;

        permutation_type::unrank(k, 8, permutation);

        state_space.clear();

        permutation_entropy<>::partition_state_space(permutation, dimension, delay, state_space);

        for(index_type k = 0; k < state_space.size(); k += 3)
        {
            auto key = 0;

            calc_key(state_space[k + 0], state_space[k + 1], state_space[k + 2], key)

            std::wcout << pm[key] << L' ';
        }

        std::wcout << std::endl;

        for(auto [k, v] : enumerate(state_space))
        {
            std::wcout << v << L' ';
        }

        std::wcout << std::endl;
    }
}

void test_zigzag()
{
    std::vector<int> matrix2d { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    std::vector<int> result;

    misc::zigzag<int, int>(matrix2d, 3, 4, result);

    for(auto e : result)
    {
        std::wcout << e << L' ';
    }

    std::wcout << std::endl;
}
