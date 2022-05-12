import random as rnd


def find_lru(cache):
    for i in range(len(cache)):
        if cache[i][1][0] >= 0:
            min_value = cache[i][1][0]
    index = 0
    for i in range(len(cache)):
        if 0 <= cache[i][1][0] <= min_value:
            min_value = cache[i][1][0]
            index = i
    return index


def find_lru2(cache):
    not_k_requested = []
    foo = [-1, [-1] * 2]
    for i in range(len(cache)):
        for j in range(2):
            if cache[i][1][j] == -1:
                not_k_requested.append(cache[i])
                break
        if len(not_k_requested) != i + 1:
            not_k_requested.append(foo)
    if len(not_k_requested) == 0:
        index = find_lru(cache)
    else:
        index = find_lru(not_k_requested)
    return index


def find_same_request(cache, request):
    for i in range(len(cache)):
        if cache[i][0] == request:
            return i
    return -1


def find_empty_cell(cache):
    for i in range(len(cache)):
        if cache[i][0] == -1:
            return i


def push_value(history_requests, value):
    history_requests[1] = history_requests[0]
    history_requests[0] = value
    return history_requests


f_data = open('data.txt', 'w')
f_answer = open('answers.txt', 'w')

for j in range(3):
    # size_cache = 3
    # number_requests = 7
    # numbers = list(map(int, list(
    #     '1 2 3 3 2 1 4'.split())))

    size_cache = rnd.randint(2, 25)
    number_requests = rnd.randint(2 * size_cache, 10 * size_cache)
    numbers = []
    for i in range(number_requests):
        numbers.append(rnd.randint(0, 10))

    f_data.write(str(j + 1) + '. ' + str(size_cache) + ' ' + str(number_requests) + '\n   ' + (
        ' '.join(map(str, numbers))) + '\n')

    history_requests = [-1] * 2

    cache = [[-1, history_requests] for i in range(size_cache)]
    cash_hit = 0

    for i in range(number_requests):
        index = find_same_request(cache, numbers[i])
        if index >= 0:
            history_requests = push_value(cache[index][1], i)
            cache[index][1] = history_requests
            cash_hit += 1
        elif cache[-1][1][0] == -1:
            index = find_empty_cell(cache)
            cache[index] = [numbers[i], [i, -1]]
        else:
            lru_index = find_lru2(cache)
            cache.pop(lru_index)
            history_requests = [i, -1]
            cache.insert(lru_index, [numbers[i], history_requests])

    f_answer.write((str(j + 1) + '. ' + str(cash_hit) + '\n'))

    print(cash_hit)

f_data.close()
f_answer.close()
