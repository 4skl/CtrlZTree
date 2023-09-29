# base algorithm slower version
def lcs(input1: str, input2: str, ret_cache=False) -> str:
    """Return the longest common subsequence of a string."""
    cache = [ ['']*(len(input2)+1) for _ in range(len(input1)+1) ]
    i = 0
    j = 0
    for i in range(1, len(input1)+1):
        for j in range(1, len(input2)+1):
            if input1[i-1] == input2[j-1]:
                cache[i][j] = cache[i-1][j-1] + input1[i-1]
            else:
                cache[i][j] = max(cache[i][j-1], cache[i-1][j], key=len)
    if ret_cache:
        return cache[i][j], cache
    return cache[i][j]

# base algorithm faster version
def lcsm(input1: str, input2: str, ret_cache=False) -> str:
    start = 1
    i_end = len(input1) # m = 
    j_end = len(input2) # n =
    # trim off the matching items at the beginning
    while start <= i_end and start <= j_end and input1[start-1] == input2[start-1]:
        start += 1
    # trim off the matching items at the end
    while start <= i_end and start <= j_end and input1[i_end-1] == input2[j_end-1]:
        i_end -= 1
        j_end -= 1
    if not ret_cache:
        return input1[:start-1] + lcs(input1[start-1:i_end], input2[start-1:j_end]) + input1[i_end:j_end]
    else:
        lcs_out, cache = lcs(input1[start-1:i_end], input2[start-1:j_end], ret_cache=True)
        return input1[:start-1] + lcs_out + input1[i_end:], cache

# fast algoritm creating output for diff
def lcs_diff(input1: str, input2: str) -> str:
    start = 1
    i_end = len(input1) # m = 
    j_end = len(input2) # n =
    # trim off the matching items at the beginning
    while start <= i_end and start <= j_end and input1[start-1] == input2[start-1]:
        start += 1
    # trim off the matching items at the end
    while start <= i_end and start <= j_end and input1[i_end-1] == input2[j_end-1]:
        i_end -= 1
        j_end -= 1
    lcs_out, cache = lcs(input1[start-1:i_end], input2[start-1:j_end], ret_cache=True)
    return input1[:start-1] + lcs_out + input1[i_end:], cache, start, i_end, j_end

# computing and printnig the diff
def print_diff(input1, input2, cache=None, i=None, j=None, start=None, i_end=None, j_end=None):
    t_input1 = input1
    t_input2 = input2
    f_it = False
    if cache is None:
        _, cache, start, i_end, j_end = lcs_diff(input1, input2)
        for c in input1[:start-1]:
            print(" ", c)
        t_input1 = input1[start-1:i_end]
        t_input2 = input2[start-1:j_end]
        f_it = True
    if i is None:
        i = len(t_input1)
    if j is None:
        j = len(t_input2)
    if i > 0 and j > 0 and t_input1[i-1] == t_input2[j-1]:
        print_diff(t_input1, t_input2, cache=cache, i=i-1, j=j-1)
        print(" ", t_input1[i-1])
    elif j > 0 and (i == 0 or len(cache[i][j-1]) >= len(cache[i-1][j])):
        print_diff(t_input1, t_input2, cache=cache, i=i, j=j-1)
        print("+",t_input2[j-1])
    elif i > 0 and (j == 0 or len(cache[i][j-1]) < len(cache[i-1][j])):
        print_diff(t_input1, t_input2, cache=cache, i=i-1, j=j)
        print("-", t_input1[i-1])
    else:
        print("")
    if f_it:
        for c in input1[i_end:]:
            print(" ", c)

def diff_on_file(filename1, filename2):
    text1 = open(filename1).read()
    text2 = open(filename2).read()
    sol, cache = lcs(text1, text2, ret_cache=True)
    print(sol)
    print_diff(cache, text1, text2)

fudof = diff_on_file
text1 = "BAZERTY"
text2 = "AZDFTY"
print_diff(text1, text2)