import numpy as np
import pandas as pd

def factorial(n):
    assert(n >= 0)
    if n <= 1:
        return 1
    else:
        return n * factorial(n-1)
    
def pk(lmbda, k):
    return np.exp(-lmbda) * (np.power(lmbda, k)/factorial(k))

def generate_data(lambdas, T = 100, file_name = "data.csv"):
    X = np.array([int(t) for t in range(T)]).astype(int).reshape(T,1)
    for i in range(lambdas.shape[0]):
        C = np.array([])
        for t in range(T):
            if np.random.uniform(0,1) < pk(lambdas[i], 1):
                C = np.append(C, 1).astype(int)
            else:
                C = np.append(C, 0).astype(int)
        X = np.append(X, C.reshape(T, 1), axis = 1)
    head  = ["Time"]
    head += ["Customer_"+str(i+1) for i in range(lambdas.shape[0])]
    df = pd.DataFrame(X)
    df.columns = head
    return df.to_csv(file_name, index = False)

nbr_customers = 10
nbr_dataset   = 10

lambdas = np.array([0.2 for i in range(nbr_customers)])
for i in range(nbr_dataset):
    generate_data(lambdas, T = 480, file_name = 'data_'+str(i+1)+'.csv')