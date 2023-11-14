# Латыпов Шамиль Ильдарович
# Группа 523
# Задание 5.

from sklearn.base import BaseEstimator, ClassifierMixin
import numpy as np

class CustomClassifier(BaseEstimator, ClassifierMixin):
    def __init__(self, loss_function):
        self.loss_function = loss_function

    def fit(self, X, y):
        return self

    def predict(self, X):
        # X - содержит вектора апостериорных вероятностей
        predictions = []
        for posterior_probabilities in X:
            expected_losses = []
            for action in range(len(posterior_probabilities)):
                # Вычисление ожидаемых потерь для каждого возможного действия
                expected_loss = sum(
                    self.loss_function(i, action) * posterior_probabilities[i]
                    for i in range(len(posterior_probabilities))
                )
                expected_losses.append(expected_loss)

            # Выбор действия с минимальными ожидаемыми потерями
            optimal_action = np.argmin(expected_losses)
            predictions.append(optimal_action)

        return np.array(predictions)

# Пример функции потерь
def example_loss_function(y_true, y_pred):
    # Задается матрица потерь размера (k x s)
    L = np.array(...)
    """
    Пример:
    L = np.array([
        [0, 1, 2],
        [1, 0, 1],
        [2, 1, 0]
    ])
    """
    
    return L[y_true, y_pred]

# classifier = CustomClassifier(loss_function=example_loss_function)
# classifier.fit(X_train, y_train)
# y_pred = classifier.predict(X_test_with_posterior_probabilities)
