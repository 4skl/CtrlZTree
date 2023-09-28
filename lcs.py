def lcs(input1: str, input2: str, ret_cache=False) -> str:
    """Return the longest common subsequence of a string."""
    cache = [ ['']*(len(input1)) for _ in range(len(input2)+1) ]
    if len(input1) == 0 or len(input2) == 0:
        if ret_cache:
            return '', cache
        return ''
    # trim beggining
    start = 1
    while start < len(input1) and start <= len(input2) and input1[start] == input2[start]:
        start += 1
    #trim ending
    end1 = len(input1)
    end2 = len(input2)
    while start < end1 and start < end2 and input1[end1-1] == input2[end2-1]:
        end1 -= 1
        end2 -= 1
    i1 = start
    i2 = start
    for i1 in range(start, end1):
        for i2 in range(start, end2):
            if input1[i1] == input2[i2]:
                cache[i1-start][i2-start] = cache[i1-1-start][i2-1-start] + input1[i1]
            else:
                cache[i1-start][i2-start] = max(cache[i1-start][i2-1-start], cache[i1-1-start][i2-start], key=len)
    print(i1, i2, len(cache), len(cache[0]))
    if ret_cache:
        return cache[i1-start-1][i2-start-1], cache
    return cache[i1-start-1][i2-start-1]
    
def print_diff(cache, input1, input2, i=None, j=None):
    print(cache)
    if i is None:
        i = len(cache)
    if j is None:
        j = len(cache[0])
    if i >= 0 and j >= 0 and input1[i] == input2[j]:
        print_diff(cache, input1, input2, i-1, j-1)
        print("  " + input1[i])
    elif j > 0 and (i == 0 or len(cache[i][j-1]) >= len(cache[i-1][j])):
        print_diff(cache, input1, input2, i, j-1)
        print("+ " + input2[j])
    elif i > 0 and (j == 0 or len(cache[i][j-1]) < len(cache[i-1][j])):
        print_diff(cache, input1, input2, i-1, j)
        print("- " + input1[i])
    else:
        print("")

def fucked_up_diff_on_file(filename1, filename2):
    text1 = open(filename1).read()
    text2 = open(filename2).read()
    sol, cache = lcs(text1, text2, ret_cache=True)
    print(sol)
    print_diff(cache, text1, text2)

fudof = fucked_up_diff_on_file