import numpy as np
from typing import List

#x = [1, 2, 3, 4]
#x = [6, 1, 0, 3, 0, 0, 5, 7, 15]

x = [[1, 2, 3], [4, 5, 6]]

print(x)

def max_after_zero(x):
    zero_poses = np.argwhere(x == 0)
    zero_poses = zero_poses + 1
    if len(zero_poses) == 0:
        return -1
    if zero_poses[-1] == len(x) and len(x) > 1:
        zero_poses = zero_poses[:-1]
        return x[zero_poses].max()
    else:
        return -1

#max_after_zero(x)



def prod_non_zero_diag(X: List[List[int]]) -> int:
    check = False
    prod = 1
    i = 0
    for i in range(min(len(X), len(X[i]))):
        if X[i][i] != 0:
            check = True
            prod *= X[i][i]
    if check:
        return prod
    else:
        return -1


#print(prod_non_zero_diag(x))


class MinMaxScaler:
    def fit(self, data):
        self.min = np.amin(data, axis=0)
        self.max = np.amax(data, axis=0)
        
    def transform(self, data):
        data -= self.min
        data /= (self.max - self.min)
        return data

class StandardScaler:
    def fit(self, data):
        self.E = np.mean(data, axis=0)
#        self.D = (np.mean(data ** 2, axis=0) - self.E ** 2) ** 0.5
        
    def transform(self, data):
    #        data = (data - self.E) / self.D
        return data


data = [[1, 2], [2, -1], [3, 0]]
print("Here ", len(data))
E = np.mean(data, axis=0)
print("E = ", E)
scaler = StandardScaler()
print(scaler.fit(data))
print(scaler.mean_)
#    [0.5 0.5]
print(scaler.transform(data))
"""    [[-1. -1.]
     [-1. -1.]
     [ 1.  1.]
     [ 1.  1.]]
"""
print(scaler.transform([[2, 2]]))
#    [[3. 3.]]




def kfold_split(num_objects, num_folds):
    n = num_objects // num_folds
    indexes = np.arange(num_objects)
    return_value = []
    k = 0
    for i in range(num_folds):
        if (i == num_folds - 1):
            k = num_objects % num_folds
        b = np.array([j for j in range(i * n, (i + 1) * n + k)])
        return_value.append((np.delete(indexes, np.s_[i * n:(i + 1) * n + k]), b))
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





def knn_cv_score(X, y, parameters, score_function, folds, knn_class):
    dii = {}
    for n in parameters['n_neighbors']:
        for n1 in parameters['metrics']:
            for n2 in parameters['weights']:
                for n3 in parameters['normalizers']:
                    func, name = n3
                    scaler = func
                    l = name,n,n1,n2
                    score = np.array([])
                    for item in folds:
                        a, b = item
                        X_scaled = X.copy()
                        if scaler is not None:
                            scaler.fit(X_scaled)
                            X_scaled = scaler.transform(X_scaled)
                        aaa = knn_class(n, weights = n2, metric =  n1)
                        h = aaa.fit(X_scaled[a],y[a]).predict(X_scaled[b])
                        score = np.hstack((score,score_function(y[b],h)))
                    dii.update([((l),score.mean())])
    return dii



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





"""Takes train data, counts cross-validation score over grid of parameters (all possible parameters combinations) 

    Parameters:
    X (2d np.array): train set
    y (1d np.array): train labels
    parameters (dict): dict with keys from {n_neighbors, metrics, weights, normalizers}, values of type list,
                       parameters['normalizers'] contains tuples (normalizer, normalizer_name), see parameters
                       example in your jupyter notebook
    score_function (callable): function with input (y_true, y_predict) which outputs score metric
    folds (list): output of kfold_split
    knn_class (obj): class of knn model to fit

    Returns:
    dict: key - tuple of (normalizer_name, n_neighbors, metric, weight), value - mean score over all folds
    """