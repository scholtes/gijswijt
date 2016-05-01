from sys import argv, stdout

def max_k(lst):
    len_lst = len(lst)
    record = 1
    for ln in range(1, len_lst/2+1):
        cur_max = 1
        pos = len_lst
        curr_chunk = lst[pos-ln:pos]
        pos -= ln
        while pos >= ln:
            if lst[pos-ln:pos] != curr_chunk:
                break
            cur_max += 1
            pos -= ln
        record = max(record, cur_max)
    return record

# Generate each term sequentially
def naive_generate(n):
    lst = [1]
    for i in range(1,n):
        lst.append(max_k(lst))
    return lst

# Use recursive formula to generate chunks of blocks
# Only the glue sequences are computed sequentially
def fast_generate(n):
    lst = [1]
    block = lst
    while len(lst) < n:
        lst = block + block
        nxt = max_k(lst)
        while nxt != 1 and len(lst)<n:
            lst.append(nxt)
            nxt = max_k(lst)
        block = lst
    return lst[0:n]

if __name__ == "__main__":
    results = fast_generate(int(argv[1]))
    for i in results:
        stdout.write("%d " % i)