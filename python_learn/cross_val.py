import numpy as np
from collections import defaultdict

def kfold_split(num_objects, num_folds):
    n = num_objects // num_folds
    indexes = np.arange(num_objects)
    return_value = []
    k = 0
    for i in range(num_folds):
        if (i == num_folds - 1):
            k = num_objects % num_folds
        b = np.array([j for j in range(i * n, (i + 1) * n + k)])
        return_value.append((np.delete(indexes, np.s_[i * n:(i + 1) * n + k]),b))
    return return_value


def knn_cv_score(X, y, parameters, score_function, folds, knn_class):
    return_dict = {}
    for i1 in parameters['n_neighbors']:
        for i2 in parameters['metrics']:
            for i3 in parameters['weights']:
                for i4 in parameters['normalizers']:
                    scaler, name = i4
                    l = name, i1, i2, i3
                    score = np.array([])
                    for object in folds:
                        a, b = object
                        X_scaled = X.copy()
                        if scaler != None:
                            scaler.fit(X_scaled)
                            X_scaled = scaler.transform(X_scaled)
                        data = (knn_class(i1, weights = i3, metric = i2)).fit(X_scaled[a],y[a]).predict(X_scaled[b])
                        score = np.hstack((score, score_function(y[b], data)))
                    return_dict.update([((l), score.mean())])
    return return_dict

 