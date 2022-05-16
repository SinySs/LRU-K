import random as rnd


def push_value(arr, value):
    for i in range(1, len(arr)):
        arr[-i] = arr[-i - 1]
    arr[0] = value
    return arr


def update_history(value, number_request, history):
    history[value] = push_value(history[value].copy(), number_request)
    return history


def find_victim(cache, history):
    for i in range(len(cache)):
        cache_elem = cache[i]
        if history[cache_elem][-1] < 0:
            return i
    return -1


def is_inf(value, history):
    if history[value][-1] < 0:
        return True
    return False


def find_less_request(cache, history, value):
    lrv_number = history[value][-1]
    lrce_number = history[cache[0]][-1]
    if lrv_number >= lrce_number:
        return 0

    for i in range(1, len(cache)):
        lrce_number_c = history[cache[i - 1]][-1]
        lrce_number_n = history[cache[i]][-1]

        if lrce_number_n <= lrv_number < lrce_number_c:
            return i
        if lrce_number_n < 0:
            return i

    return -1


f_data = open('data.txt', 'w')
f_answer = open('answers.txt', 'w')

k = 3

for j in range(5):
    cash_hit = 0

    # size_cache = 4
    # cache = [-1] * size_cache
    #
    # number_requests = 12
    # max_number = 5
    # numbers = list(map(int, '1 2 3 4 1 2 5 1 2 4 3 4'.split()))

    size_cache = int(input('Enter len cache '))
    cache = [-1] * size_cache

    number_requests = int(input('Enter number of requests '))
    max_number = int(input('Enter max number request '))
    numbers = []
    for i in range(number_requests):
        numbers.append(rnd.randint(0, max_number))

    history_request = [-1] * k
    history = [history_request for i in range(max_number + 1)]

    f_data.write(str(size_cache) + ' ' + str(number_requests) + ' ' + (' '.join(map(str, numbers))) + '\n')

    for i in range(number_requests):
        number = numbers[i]
        history = update_history(number, i, history)
        if number in cache:
            cash_hit += 1
            if is_inf(number, history):
                index = find_victim(cache, history)
                cache.pop(cache.index(number))
                cache.insert(index, number)
            else:
                index = find_less_request(cache, history, number)
                cache.pop(cache.index(number))
                cache.insert(index, number)
        else:
            if is_inf(number, history):
                index = find_victim(cache, history)
                cache.insert(index, number)
                cache.pop()
            else:
                index = find_less_request(cache, history, number)
                cache.insert(index, number)
                cache.pop()

    f_answer.write(str(cash_hit) + '\n')

    print(cash_hit)

f_data.close()
f_answer.close()
