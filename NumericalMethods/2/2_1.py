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

def LU(A: np.array):
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

    for i in range(n):
        if(i != 0):
            for k in range(i,n):
                for l in range(i, n):
                    result[k, l] -= result[k, i-1]*result[i-1, l]
        if(i == n-1):
            break
        newCols, newRows = findMax(result, i)

        changeCols(result,i ,newCols)
        changeColsVec(P, i, newCols)

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

    return (P_mat, Q_mat, L, U)

def det_LU(U: np.array):
    n = U.shape[0]
    result = 1
    for i in range(n):
        result *= U[i,i]
    return result

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

def LU_check(A: np.array):# проверка решения
    n = A.shape[0]
    P,Q, L, U = LU(A)
    left =  P @ A @ Q
    right = L @ U
    for i in range(n):
        for j in range(n):
            if(abs(left[i][j] - right[i][j]) > 0.0000001):
                return False
    return True

def BigCheckLU(quantity, size):
    sucess = 0
    fail = 0
    for i in range(quantity):
        check_matrix = np.random.randint(0,size=(size, size),high=100)# генерируем случайную матрицу
        while np.linalg.det(check_matrix) == 0:
            check_matrix = np.random.randint(0,size=(size, size),high=100)

        flag = LU_check(check_matrix)# проверяем
        if(flag == False):
            fail += 1
        else:
            sucess += 1
    return (sucess, fail)

def det_check(A: np.array):
    lu_res = LU(A)
    det = det_LU(lu_res[3])
    if(abs(abs(det) - abs(np.linalg.det(A))) >  0.001):
        return False
    return True

def BigCheckDet(quantity, size):
    sucess = 0
    fail = 0
    for i in range(quantity):
        check_matrix = np.random.randint(0,size=(size, size),high=100)# генерируем случайную матрицу
        while np.linalg.det(check_matrix) == 0:
            check_matrix = np.random.randint(0,size=(size, size),high=100)

        flag = det_check(check_matrix)# проверяем
        if(flag == False):
            fail += 1
        else:
            sucess += 1
    return (sucess, fail)

def solve_check(matrix, b, x):# проверка решения
    left = matrix @ x
    right = b
    check = left - right
    for i in range(check.shape[0]):
        if (check[i] > 0.0000001):
            return False
    return True

def BigCheckSolve(quantity, size):
    sucess = 0
    fail = 0
    for i in range(quantity):
        check_matrix = np.random.randint(0,size=(size, size),high=100)# генерируем случайную матрицу
        while np.linalg.det(check_matrix) == 0:
            check_matrix = np.random.randint(0,size=(size, size),high=100)

        result_of_matrix = np.random.randint(0,size=size,high=100)# генерируем случайный столбец ответов
        P, Q, L, U = LU(check_matrix)
        x = Q @ system_solution_LU(L, U, P @ result_of_matrix)
        flag = solve_check(check_matrix, result_of_matrix, x)# проверяем
        if(flag == False):
            fail += 1
        else:
            sucess += 1
    return (sucess, fail)

def revers_LU(P: np.array, Q: np.array, L: np.array, U: np.array):
    n = L.shape[0]
    E = np.eye(n)
    e_curr = np.zeros(n)
    A_rev = np.zeros((n,n))
    for i in range(n):
        for k in range(n):
            e_curr[k] = E[k,i]
        x = system_solution_LU(L,U, e_curr)
        for k in range(n):
            A_rev[k, i] = x[k]
    return Q @ A_rev @ P

def revers_check(A: np.array):
    n = A.shape[0]
    lu_res = LU(A)
    L = lu_res[2]
    U = lu_res[3]
    P = lu_res[0]
    Q = lu_res[1]
    rev = revers_LU(P, Q, L, U)
    num_rev = np.linalg.inv(A)
    for i in range(n):
        for j in range(n):
            if(abs(rev[i][j] - num_rev[i][j]) > 0.001):
                return False
    return True

def BigCheckInv(quantity, size):
    sucess = 0
    fail = 0
    for i in range(quantity):
        check_matrix = np.random.randint(0,size=(size, size),high=100)# генерируем случайную матрицу
        while np.linalg.det(check_matrix) == 0:
            check_matrix = np.random.randint(0,size=(size, size),high=100)
        flag = revers_check(check_matrix)# проверяем
        if(flag == False):
            fail += 1
        else:
            sucess += 1
    return (sucess, fail)

def norm(A: np.array):
    n = A.shape[0]
    max = abs(A[0, 0])
    for j in range(n):
        sum = 0
        for i in range(n):
            sum += abs(A[i, j])
        if sum > max:
            max = sum
    return max

def conditionNumber(A: np.array):
    res_lu = LU(A)
    A_rev = revers_LU(res_lu[0], res_lu[1], res_lu[2], res_lu[3])
    return norm(A)*norm(A_rev)

def CondNumberCheck(A: np.array):
    my = conditionNumber(A)
    numppy = np.linalg.norm(A, 1) * np.linalg.norm(np.linalg.inv(A), 1)
    if(abs(my - numppy) > 0.000001):
        return False
    return True

def BigCheckCond(quantity, size):
    sucess = 0
    fail = 0
    for i in range(quantity):
        check_matrix = np.random.randint(0,size=(size, size),high=100)# генерируем случайную матрицу
        while np.linalg.det(check_matrix) == 0:
            check_matrix = np.random.randint(0,size=(size, size),high=100)
        flag = CondNumberCheck(check_matrix)# проверяем
        if(flag == False):
            fail += 1
        else:
            sucess += 1
    return (sucess, fail)

print(BigCheckSolve(100,5))