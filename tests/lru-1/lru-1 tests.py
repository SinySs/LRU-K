import random as rnd


def find_lru(cache):
    min_value = cache[0][1]
    index = 0
    for i in range(len(cache)):
        if cache[i][1] <= min_value:
            min_value = cache[i][1]
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


f = open('data.txt', 'w')
f_1 = open('answers.txt', 'w')

for j in range(3):
    size_cache = rnd.randint(2, 25)
    number_requests = rnd.randint(2 * size_cache, 10 * size_cache)

    numbers = []
    for i in range(number_requests):
        numbers.append(rnd.randint(0, 10))

    f.write(str(j + 1) + '. ' + str(size_cache) + ' ' + str(number_requests) + '\n   ' + (
        ' '.join(map(str, numbers))) + '\n')

    cache = [[-1, 0] for i in range(size_cache)]

    cash_hit = 0

    for i in range(number_requests):
        index = find_same_request(cache, numbers[i])
        if index >= 0:
            cache[index][1] = i
            cash_hit += 1
        elif cache[-1][1] == 0:
            index = find_empty_cell(cache)
            cache[index] = [numbers[i], i]
        else:
            lru_index = find_lru(cache)
            cache.pop(lru_index)
            cache.insert(lru_index, [numbers[i], i])

    f_1.write((str(j + 1) + '. ' + str(cash_hit) + '\n'))

    print(cash_hit)

f.close()
f_1.close()
