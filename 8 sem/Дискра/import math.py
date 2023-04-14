import math
from solver import ListSolver

def main():
    # Read input
    n, m = map(int, input().split())
    c = list(map(float, input().split()))
    p = list(map(float, input().split()))
    w = [list(map(float, input().split())) for _ in range(n)]

    # Initialize variables
    lambda_ = [1.0] * (m - 1)
    copy_w = [w[i][m - 1] for i in range(n)]
    iter_count, iter_number, eps, loss = 25000, 1, 0.0001, 0
    solver = ListSolver(n, c[m - 1])

    # Run optimization loop
    while iter_number <= iter_count:
        # Compute new values for p and loss
        copy_p = [0] * n
        sum_c = 0
        for i in range(n):
            sum_pi = sum(w[i][j] * lambda_[j] for j in range(m - 1))
            if not i:
                sum_c = sum(c[j] * lambda_[j] for j in range(m - 1))
            copy_p[i] = p[i] - sum_pi

        # Find subset with maximum value
        result = [False] * n
        values = solver.solve(copy_w, copy_w)
        max_p, max_indices = values[0], values[1]
        for index in max_indices:
            result[index] = True

        # Check convergence
        if eps > abs(max_p + sum_c - loss):
            break
        else:
            loss = max_p + sum_c

        # Compute new values for lambda
        D = [0] * (m - 1)
        for i in range(m - 1):
            sum_w = sum(w[j][i] for j in range(n) if result[j])
            D[i] = c[i] - sum_w
        D_abs = math.sqrt(sum(D[i] * D[i] for i in range(m - 1)))
        for i in range(m - 1):
            lambda_[i] = max(lambda_[i] - 1 / iter_number * D[i] / (D_abs + eps), 0)
        iter_number += 1

    # Print results
    print(loss)
    for i in range(m - 1):
        print(lambda_[i])

if __name__ == '__main__':
    main()
