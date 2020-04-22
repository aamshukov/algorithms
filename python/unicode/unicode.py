import sys

def list_category(category):
    with open(r"D:\Tmp\UnicodeData.txt") as stream:
        baskets = []
        index = -1
        curr_num = -1
        for _, line in enumerate(stream):
            num, _, cat, _ = line.split(';', 3)
            if cat == category:
                num = int(num, 16)
                if num - curr_num != 1:
                    baskets.append([])
                    index += 1
                baskets[index].append(num)
                curr_num = num
        result = baskets
    return result


def main(args):
    # main(['Cf'])
    category = args[0]
    print("Listing  {}  category ...".format(category))
    ranges = list_category(category)
    # print(ranges)
    result = "    return\n"
    for r in ranges:
        def convert(num):
            result = "{0:#0{1}x}".format(num, 6)
            result = list(result)
            prefix = result[0:2]
            suffix = result[2:]
            suffix = [ch.upper() for ch in suffix]
            result = ''.join(prefix) + ''.join(suffix)
            return result
        start = convert(r[0])
        end = convert(r[len(r)-1])
        # print("{}, {}".format(start, end))
        result += "           in_range(codepoint, {}, {}) ||\n".format(start, end)
    result += ";"
    print(result)


# (python38-64bit) D:\Tmp>python D:\Projects\algorithms\python\unicode\unicode.py Pc
if __name__ == '__main__':
    main(sys.argv[1:])
    exit(0)
