import numpy as np

def changeColsVec(A: np.array, first: int, second: int):
    n = A.shape
    tmp = A[first].copy()
    A[first] = A[second]
    A[second] = tmp

def changeCols(A: np.array, first: int, second: int):
    n = A.shape[0]
    tmp = A[first, 0:n].copy()
    A[first, 0:n] = A[second, 0:n]
    A[second, 0:n] = tmp

def changeRows(A: np.array, first: int, second: int):
    n = A.shape[0]
    tmp = A[0:n, first].copy()
    A[0:n, first] = A[0:n, second]
    A[0:n, second] = tmp

def findMax(A: np.array, numberStep: int):
    n = A.shape[0]
    max = A[numberStep][numberStep]
    maxCols = numberStep
    maxRows = numberStep
    for i in range(numberStep,n):
        for j in range(numberStep, n):
            if(abs(A[i][j]) > max):
                max = A[i][j]
                maxCols = i
                maxRows = j
    return (maxCols, maxRows)

def rankMat(A:np.array):
    n_row = A.shape[1]
    n_col = A.shape[0]
    rank = 0

    for i in range(n_col):
        newCols, newRows = findMax(A, i)
        if(abs(A[newCols, newRows]) < 0.00000000000001):
            break
        rank += 1
        changeCols(A,i ,newCols)
        changeRows(A,i ,newRows)

        for j in range(i+1, n_col):
            kef = A[j, i] / A[i, i]
            for l in range(i, n_row):
                A[j, l] -= kef * A[i, l]

    return rank

def system_solution_LU(L: np.array,U: np.array, b:np.array):
    n = L.shape[0]
    Y = np.zeros(n,dtype='float64')
    X = np.zeros(n,dtype='float64')

    for i in range(n):
        Y[i] = b[i]
        j = 0
        while(j < i):
            Y[i] -= L[i][j]*Y[j]
            j += 1

    i = n - 1
    while(i >= 0):
        X[i] = Y[i]
        j = n - 1
        while(j > i):
            X[i] -= U[i][j]*X[j]
            j -= 1
        X[i] /= U[i][i]
        i -= 1
    return X

def solve_check(P, Q,matrix, b, x):# проверка решения
    left = P @ matrix @ Q @ x
    right = b
    check = left - right
    for i in range(check.shape[0]):
        if (check[i] > 0.0000001):
            return False
    return True

def LU_dop(A: np.array, b: np.array):
    n = A.shape[0]
    P = np.zeros((n),dtype='int64')
    for i in range(n):
        P[i] = i

    Q = np.zeros((n),dtype='int64')
    for i in range(n):
        Q[i] = i

    result = np.zeros((n,n),dtype='float64')
    for i in range(n):
        for j in range(n):
            result[i, j] = A[i, j]

    rank = 0

    b_ = np.zeros(b.shape[0], dtype='float64')
    for i in range(b.shape[0]):
        b_[i] = b[i]

    for i in range(n):
        if(i != 0):
            for k in range(i,n):
                for l in range(i, n):
                    result[k, l] -= result[k, i-1]*result[i-1, l]
                b_[k] -= result[k, i-1] * b_[i-1]

        newCols, newRows = findMax(result, i)

        if(abs(result[newCols, newRows]) <  0.000000001):
            break
        rank += 1

        changeCols(result,i ,newCols)
        changeColsVec(P, i, newCols)
        changeColsVec(b_, i, newCols)

        changeRows(result,i ,newRows)
        changeColsVec(Q, i, newRows)

        for j in range(i, n):
            if(i == j):
                continue
            else:
                result[j, i] /= result[i, i]

    U = np.zeros((n,n),dtype='float64')
    for i in range(n):
        for j in range(i,n):
            U[i, j] = result[i, j]

    L = np.zeros((n,n),dtype='float64')
    for i in range(n):
        for j in range(i+1):
            if(i == j):
                L[i,j] = 1
                continue
            L[i, j] = result[i, j]

    P_mat = np.zeros((n,n),dtype='int64')
    for i in range(n):
        P_mat[i, P[i]] = 1

    Q_mat = np.zeros((n,n),dtype='int64')
    for i in range(n):
        Q_mat[Q[i], i] = 1


    rankDop = 0
    for i in range(b_.shape[0]):
        if(abs(b_[i]) < 0.0000001):
            break
        rankDop += 1

    if((rank != n) and (rank == rankDop)):
        P_mat = np.eye(n)

    return (P_mat, Q_mat, L, U, rank, rankDop, P)

def UltimateSolution(P_mat, Q_mat, L, U, rank, rankDop, P, b):
    n = L.shape[0]
    if(rank == n):
        return P_mat @ system_solution_LU(L, U, b)

    if(rank != rankDop):
        return rank

    L_ = np.zeros((rank,rank),dtype='float64')
    U_ = np.zeros((rank,rank),dtype='float64')
    for i in range(rank):
        for j in range(rank):
            L_[i, j] = L[i,j]
            U_[i, j] = U[i,j]
    b_ = np.zeros(rank, dtype='float64')
    for i in range(rank):
        b_[i] = b[P[i]]
    x_ = system_solution_LU(L_, U_, b_)
    x = np.zeros(n, dtype='float64')
    for i in range(rank):
        x[i] = x_[i]
    return x

A = np.array([(2,0,7, -5, 11),(1,-2,3,0,2),(-3,9,-11,0,-7),(-5, 17, -16, -5,-4),(7,-17,23,0,15)])
b = np.array((42, 17, -64, -90, 132))
lu = LU_dop(A, b)
x = UltimateSolution(lu[0], lu[1], lu[2], lu[3], lu[4], lu[5], lu[6], b)
print(solve_check(lu[0], lu[1], A, b, x))