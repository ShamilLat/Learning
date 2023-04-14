import math
from solver import ListSolver

if __name__ == '__main__':
    n, m = map(int, input().split())
    c = list(map(float, input().split()))
    p = list(map(float, input().split()))
    w = [list(map(float, input().split())) for _ in range(n)]

    lambda_ = [1.0] * (m - 1)
    copy_w = [w[i][m - 1] for i in range(n)]

    iter_count, iter_number, eps, loss = 25000, 0, 0.0001, 0
    solver = ListSolver(n, c[m - 1])

    while iter_number <= iter_count:
        iter_number += 1
        
        copy_p = [0] * n
        sum_c = 0

        for i in range(n):
            sum_pi = sum(w[i][j] * lambda_[j] for j in range(m - 1))
            copy_p[i] = p[i] - sum_pi

        sum_c = sum(c[j] * lambda_[j] for j in range(m - 1))
        
        values = solver.solve(copy_w, copy_p)
        max_p, indices = values[0], values[1]

        if eps > abs(max_p + sum_c - loss):
            break
        
        loss = max_p + sum_c
        D = [0] * (m - 1)

        for i in range(m - 1):
            sum_w = sum(w[j][i] for j in indices)
            D[i] = c[i] - sum_w

        D_abs = math.sqrt(sum(D[i] * D[i] for i in range(m - 1)))

        for i in range(m - 1):
            lambda_[i] = max(lambda_[i] - 1 / iter_number * D[i] / (D_abs + eps), 0)


    print(loss)
    for i in range(m - 1):
        print(lambda_[i])
