import numpy as np

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
        self.D = (np.mean(data ** 2, axis=0) - self.E ** 2) ** 0.5
        
    def transform(self, data):
        data = (data - self.E) / self.D
        return data
