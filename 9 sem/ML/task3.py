# Латыпов Шамиль Ильдарович
# Группа 523
# Задание 3: Выборка, вероятность --> оптимальный интервал

import numpy as np
from scipy.stats import norm
from scipy.optimize import minimize

# Выборка данных
sample_data = np.random.normal(5, 20, 1000)

p = 0.95

# Оценка параметров распределения из выборки
mu, std = norm.fit(sample_data)

# Функция для поиска оптимального интервала
def find_optimal_interval_from_sample(mu, std, p):
    # Функция, которую мы хотим минимизировать
    def objective(x):
        a, b = x
        return b - a

    # Функция ограничения для вероятности p
    def constraint(x):
        a, b = x
        return norm.cdf(b, mu, std) - norm.cdf(a, mu, std) - p

    # Начальные границы для a и b
    a_initial = norm.ppf((1 - p) / 2, mu, std)
    b_initial = norm.ppf(1 - (1 - p) / 2, mu, std)
    
    # Оптимизация
    result = minimize(
        objective,
        np.array([a_initial, b_initial]),
        constraints={'type': 'eq', 'fun': constraint},
        bounds=[(a_initial, b_initial), (a_initial, b_initial)]
    )
    
    a, b = result.x
    return a, b

a, b = find_optimal_interval_from_sample(mu, std, p)
print(f"Оптимальный интервал для p={p} на основе выборки данных: [{a}, {b}]")
