# Латыпов Шамиль Ильдарович
# Группа 523
# Задание 4: Распределение, вероятность --> оптимальный интервал

import numpy as np
from scipy.stats import norm
from scipy.optimize import minimize

# Заданное распределение
mu = 5
std = 20
dist = norm(loc=mu, scale=std)

p = 0.95

# Функция для поиска оптимального интервала
def find_optimal_interval_from_distribution(dist, p):
    # Функция, которую мы хотим минимизировать
    def objective(x):
        a, b = x
        return b - a

    # Функция ограничения для вероятности p
    def constraint(x):
        a, b = x
        return dist.cdf(b) - dist.cdf(a) - p

    # Начальные границы для a и b
    a_initial = dist.ppf((1 - p) / 2)
    b_initial = dist.ppf(1 - (1 - p) / 2)
    
    # Оптимизация
    result = minimize(
        objective,
        np.array([a_initial, b_initial]),
        constraints={'type': 'eq', 'fun': constraint},
        bounds=[(a_initial, b_initial), (a_initial, b_initial)]
    )
    
    a, b = result.x
    return a, b

a, b = find_optimal_interval_from_distribution(dist, p)
print(f"Оптимальный интервал для p={p} с параметрами распределения: [{a}, {b}]")
