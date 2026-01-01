"""
def calc_score(arr, cur_val):
    score = 0
    # 累计日志条数
    total = 0
    for i in range(cur_val + 1):
        if total + arr[i] < 100:
            # 直接奖励分
            score += arr[i]
            # 延迟上报扣分
            score -= arr[i] * (cur_val - i)
            total += arr[i]
        else:
            # 超过100条，强制上报
            score = 100 - total
            return score

    return score


def solve_method(arr):
    score = 0

    if len(arr) > 0 and arr[0] >= 100:
        return 100

    for i in range(len(arr)):
        score = max(score, calc_score(arr, i))

    return score


if __name__ == "__main__":
    tests = [[1,2,3,4,40,70], [50, 60, 1]]
    for t in tests:
        result = solve_method(t)
        print("solve_method({}) = {}".format(t, result))
"""

"""
def merge(ports):
    for i in range(len(ports)):
        for j in range(i + 1, len(ports)):
            seti = set(ports[i])
            setj = set(ports[j])
            merge_set = seti.union(setj)
            if len(merge_set) <= len(seti) + len(setj) - 2:
                ports[i] = list(merge_set)
                ports.pop(j)
                return True
    return False


def solve_method(ports):
    while merge(ports):
        pass

    return [sorted(list(set(p))) for p in ports]


if __name__ == '__main__':
    ports = [[4], [2, 3], [1, 2], [3,4], [5]]
    result=solve_method(ports)
    print("solve_method({}) = {}".format(ports, result))
"""

def solve_method(img):
    avg = sum(img) // len(img)
    diff = avg - 128
    new_img = img.copy()

    k = 0
    if diff > 0:
        # 如果差值大于0，则k是负数
        while avg > 127:
            k -= 1
            avg = get_new_image_avg(new_img, k)
    if diff < 0:
        # 如果差值小于0，则k是正数
        while avg < 128:
            k += 1
            avg = get_new_image_avg(new_img, k)
    return k


def get_new_image_avg(new_img, k):
    new_img = [min(max(0, x + k), 255) for x in new_img]
    return sum(new_img) // len(new_img)


if __name__ == '__main__':
    assert solve_method([3,3,255]) == 62
    assert solve_method([129, 130, 129, 130]) == -2
