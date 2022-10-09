def process(l):
    return sorted(set([i * i for j in l for i in j]))[::-1]
