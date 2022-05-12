import random as rnd


def find_lru(cache):
    min_value = cache[0][1][0]
    index = 0
    for i in range(len(cache)):
        if cache[i][1][0] <= min_value:
            min_value = cache[i][1][0]
            index = i
    return index


def find_lru2(cache):
    min_value = 0
    index = 0
    for i in range(len(cache)):
        if cache[i][1][1] == -1:
            return -1
        elif cache[i][1][1] <= min_value:
            min_value = cache[i][1][1]
            index = i
    return index


def find_lru3(cache):
    min_value = 0
    index = 0
    for i in range(len(cache)):
        if cache[i][1][2] == -1:
            return -1
        elif cache[i][1][2] < min_value:
            min_value = cache[i][1][2]
            index = i
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
    history_requests[2] = history_requests[1]
    history_requests[1] = history_requests[0]
    history_requests[0] = value
    return history_requests


f = open('data.txt', 'w')
f_1 = open('answers.txt', 'w')

for j in range(3):
    # size_cache = 2
    # number_requests = 19
    # numbers = [8, 0, 6, 9, 4, 8, 4, 4, 2, 6, 4, 10, 0, 5, 1, 8, 0, 2, 8]

    size_cache = rnd.randint(2, 25)
    number_requests = rnd.randint(2 * size_cache, 10 * size_cache)
    numbers = []
    for i in range(number_requests):
        numbers.append(rnd.randint(0, 10))

    f.write(str(j + 1) + '. ' + str(size_cache) + ' ' + str(number_requests) + '\n   ' + (
        ' '.join(map(str, numbers))) + '\n')

    history_requests = [-1] * 3

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
            history_requests = [i, -1, -1]
            cache[index] = [numbers[i], history_requests]
        else:
            lru_index = find_lru3(cache)
            if lru_index == -1:
                lru_index = find_lru2(cache)
                if lru_index == -1:
                    lru_index = find_lru(cache)
            cache.pop(lru_index)
            history_requests = [i, -1, -1]
            cache.insert(lru_index, [numbers[i], history_requests])

    f_1.write((str(j + 1) + '. ' + str(cash_hit) + '\n'))

    print(cash_hit)

f.close()
f_1.close()
