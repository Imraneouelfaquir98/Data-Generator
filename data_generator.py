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

def generate_data(lambdas, customer_coors, T = 480, file_name = "data.csv"):
    req = 1
    X = np.array([ 0, 70, 70,-1]).reshape(1, 4)
    for t in range(T):
        for c in range(lambdas.shape[0]):
            if np.random.uniform(0,1) < pk(lambdas[c], 1):
                X = np.append(X, np.array([ req, customer_coors[c][0], customer_coors[c][1], t]).reshape(1, 4), axis = 0)
                req += 1
    head  = [ "Req", "X_Coor", "Y_Coor", "Arr"]
    df = pd.DataFrame(X)
    df.columns = head
    return df.to_csv(file_name, index = False)

nbr_customers = 10
nbr_dataset   = 10

customer_coors = np.random.randint(0, 200, (nbr_customers,2))
lambdas = np.array([0.02 for i in range(nbr_customers)])

for i in range(nbr_dataset):
    generate_data(lambdas, customer_coors, file_name = 'data_'+str(i+1)+'.csv')