import numpy as np
import math
import time

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
    arithmetic_op = 0
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
                    arithmetic_op += 2
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
                arithmetic_op += 1

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

    return (P_mat, Q_mat, L, U, arithmetic_op)

def system_solution_LU(lu_res, b:np.array):
    P_mat = lu_res[0]
    Q_mat = lu_res[1]
    L = lu_res[2]
    U = lu_res[3]
    arithmetic_op = 0
    n = L.shape[0]
    Y = np.zeros(n,dtype='float64')
    X = np.zeros(n,dtype='float64')
    b = P_mat @ b
    #arithmetic_op += n**2


    for i in range(n):
        Y[i] = b[i]
        j = 0
        while(j < i):
            Y[i] -= L[i][j]*Y[j]
            arithmetic_op += 2
            j += 1

    i = n - 1
    while(i >= 0):
        X[i] = Y[i]
        j = n - 1
        while(j > i):
            X[i] -= U[i][j]*X[j]
            j -= 1
            arithmetic_op += 2
        X[i] /= U[i][i]
        arithmetic_op += 1
        i -= 1

    #arithmetic_op += n**2
    return (Q_mat @ X, arithmetic_op)

def F(x):
    x1,x2,x3,x4,x5,x6,x7,x8,x9, x10 = x
    F = np.mat([
        math.cos(x2 * x1) - math.exp(-3 * x3) + x4 * x5 ** 2 - x6 - math.sinh(2 * x8) * x9 + 2 * x10 + 2.000433974165385440,
        math.sin(x2 * x1) + x3 * x9 * x7 - math.exp(-x10 + x6) + 3 * x5 ** 2 - x6 * (x8 + 1) + 10.886272036407019994,
        x1 - x2 + x3 - x4 + x5 - x6 + x7 - x8 + x9 - x10 - 3.1361904761904761904,
        2 * math.cos(-x9 + x4) + x5 / (x3 + x1) - math.sin(x2 ** 2) + math.cos(x7 * x10) ** 2 - x8 - 0.1707472705022304757,
        math.sin(x5) + 2 * x8 * (x3 + x1) - math.exp(-x7 * (-x10 + x6)) + 2 * math.cos(x2) - 1.0 / (-x9 + x4) - 0.3685896273101277862,
        math.exp(x1 - x4 - x9) + x5 ** 2 / x8 + math.cos(3 * x10 * x2) / 2 - x6 * x3 + 2.0491086016771875115,
        x2 ** 3 * x7 - math.sin(x10 / x5 + x8) + (x1 - x6) * math.cos(x4) + x3 - 0.7380430076202798014,
        x5 * (x1 - 2 * x6) ** 2 - 2 * math.sin(-x9 + x3) + 0.15e1 * x4 - math.exp(x2 * x7 + x10) + 3.5668321989693809040,
        7 / x6 + math.exp(x5 + x4) - 2 * x2 * x8 * x10 * x7 + 3 * x9 - 3 * x1 - 8.4394734508383257499,
        x10 * x1 + x9 * x2 - x8 * x3 + math.sin(x4 + x5 + x6) * x7 - 0.78238095238095238096], dtype="float64")

    return F

def J(x):
    x1,x2,x3,x4,x5,x6,x7,x8,x9, x10 = x
    J = np.mat([[-x2 * math.sin(x2 * x1), -x1 * math.sin(x2 * x1), 3 * math.exp(-3 * x3), x5 ** 2, 2 * x4 * x5,
                    -1, 0, -2 * math.cosh(2 * x8) * x9, -math.sinh(2 * x8), 2],
                   [x2 * math.cos(x2 * x1), x1 * math.cos(x2 * x1), x9 * x7, 0, 6 * x5,
                    -math.exp(-x10 + x6) - x8 - 1, x3 * x9, -x6, x3 * x7, math.exp(-x10 + x6)],
                   [1, -1, 1, -1, 1, -1, 1, -1, 1, -1],
                   [-x5 / (x3 + x1) ** 2, -2 * x2 * math.cos(x2 ** 2), -x5 / (x3 + x1) ** 2, -2 * math.sin(-x9 + x4),
                    1.0 / (x3 + x1), 0, -2 * math.cos(x7 * x10) * x10 * math.sin(x7 * x10), -1,
                    2 * math.sin(-x9 + x4), -2 * math.cos(x7 * x10) * x7 * math.sin(x7 * x10)],
                   [2 * x8, -2 * math.sin(x2), 2 * x8, 1.0 / (-x9 + x4) ** 2, math.cos(x5),
                    x7 * math.exp(-x7 * (-x10 + x6)), -(x10 - x6) * math.exp(-x7 * (-x10 + x6)), 2 * x3 + 2 * x1,
                    -1.0 / (-x9 + x4) ** 2, -x7 * math.exp(-x7 * (-x10 + x6))],
                   [math.exp(x1 - x4 - x9), -1.5 * x10 * math.sin(3 * x10 * x2), -x6,-math.exp(x1 - x4 - x9),
                    2 * x5 / x8, -x3, 0, -x5 ** 2 / x8 ** 2, -math.exp(x1 - x4 - x9), -1.5 * x2 * math.sin(3 * x10 * x2)],
                   [math.cos(x4), 3 * x2 ** 2 * x7, 1, -(x1 - x6) * math.sin(x4), x10 / x5 ** 2 * math.cos(x10 / x5 + x8),
                    -math.cos(x4), x2 ** 3, -math.cos(x10 / x5 + x8), 0, -1.0 / x5 * math.cos(x10 / x5 + x8)],
                   [2 * x5 * (x1 - 2 * x6), -x7 * math.exp(x2 * x7 + x10), -2 * math.cos(-x9 + x3), 1.5,
                    (x1 - 2 * x6) ** 2, -4 * x5 * (x1 - 2 * x6), -x2 * math.exp(x2 * x7 + x10), 0, 2 * math.cos(-x9 + x3),
                    -math.exp(x2 * x7 + x10)],
                   [-3, -2 * x8 * x10 * x7, 0, math.exp(x5 + x4), math.exp(x5 + x4),
                    -7.0 / x6 ** 2, -2 * x2 * x8 * x10, -2 * x2 * x10 * x7, 3, -2 * x2 * x8 * x7],
                   [x10, x9, -x8, math.cos(x4 + x5 + x6) * x7, math.cos(x4 + x5 + x6) * x7,
                    math.cos(x4 + x5 + x6) * x7, math.sin(x4 + x5 + x6), -x3, x2, x1]], dtype="float64")
    return J

x_0 = np.array([0.5, 0.5, 1.5, -1.0, -0.5, 1.5, 0.5, -0.5, 1.5, -1.5])

def f(x):
    return x - math.sin(x) - 0.25

def f_deriv(x):
    return 1 - math.cos(x)

def newton_method_root(eps = 0.0001):
    curr_x = 0.1
    while(True):
        dx = f(curr_x)/f_deriv(curr_x)
        curr_x -= dx
        if(np.linalg.norm(dx) < eps):
            break
    return curr_x

def get_dx(x, Jacobian_LU=None):
    if Jacobian_LU == None:
        arithmetic_op = 0
        lu_res = LU(J(x))
        arithmetic_op += lu_res[4]
        result = system_solution_LU(lu_res,-np.transpose(F(x)))
        arithmetic_op += result[1]
        return (result[0], arithmetic_op)
    else:
        arithmetic_op = 0
        result = system_solution_LU(Jacobian_LU,-np.transpose(F(x)))
        arithmetic_op += result[1]
        return (result[0], arithmetic_op)

def newton_method(x_0, eps = 0.000001):
    start_time = time.time()
    curr_x = x_0.copy()
    itr = 0
    arithmetic_op = 0
    while(True):
        dx, curr_op = get_dx(curr_x)
        arithmetic_op += curr_op
        curr_x += dx
        itr += 1
        if(np.linalg.norm(dx) < eps):
            break
        if(np.linalg.norm(dx) > 90 or itr > 1000):
            return False
    return curr_x, time.time() - start_time, itr, arithmetic_op

def newton_method_full_mod(eps = 0.000001):
    start_time = time.time()
    curr_x = x_0.copy()
    itr = 0
    arithmetic_op = 0
    Jacobian_LU = LU(J(x_0))
    arithmetic_op += Jacobian_LU[4]
    while(True):
        dx, curr_op = get_dx(curr_x, Jacobian_LU)
        arithmetic_op += curr_op
        curr_x += dx
        itr += 1
        if(np.linalg.norm(dx) < eps):
            break
        if(np.linalg.norm(dx) > 90 or itr > 1000):
            return False
    return curr_x, time.time() - start_time, itr, arithmetic_op

def newton_method_k_mod(k,eps = 0.000001):
    start_time = time.time()
    curr_x = x_0.copy()
    itr = 0
    arithmetic_op = 0
    Jacobian_LU = 0
    while(True):
        if(itr < k):
            dx, curr_op = get_dx(curr_x)
        else:
            if(itr == k):
                Jacobian_LU = LU(J(curr_x))
                arithmetic_op += Jacobian_LU[4]
            dx, curr_op = get_dx(curr_x, Jacobian_LU)

        arithmetic_op += curr_op
        curr_x += dx
        itr += 1
        if(np.linalg.norm(dx) < eps):
            break
        if(np.linalg.norm(dx) > 90 or itr > 1000):
            return False
    return curr_x, time.time() - start_time, itr, arithmetic_op

def newton_method_hybrid_k(k,eps = 0.000001):
    start_time = time.time()
    curr_x = x_0.copy()
    itr = 0
    arithmetic_op = 0
    Jacobian_LU = 0
    while(True):
        if(itr % k == 0):
            Jacobian_LU = LU(J(curr_x))
            arithmetic_op += Jacobian_LU[4]
        dx, curr_op = get_dx(curr_x, Jacobian_LU)
        arithmetic_op += curr_op
        curr_x += dx
        itr += 1
        if(np.linalg.norm(dx) < eps):
            break
        if(np.linalg.norm(dx) > 90 or itr > 1000):
            return False
    return curr_x, time.time() - start_time, itr, arithmetic_op

def print_newton_method_root():
    result = newton_method_root()
    print("1.1")
    print("Нахождение корня уравнения методом Ньютона")
    print(f"Корень: {result}")
    print(f"Значение {f(result)}")
    print("----------------------------------------------------------------------")

def print_newton_method(x_0):
    result = newton_method(x_0)
    print("2.a")
    print("Нахождение решения системы нелинейных уравнений методом Ньютона")
    if(result == False):
        print("ряд расходится")
    else:
        print(f"Решение {result[0]}")
        print(f"Затраченное время {result[1]}")
        print(f"Количество итераций {result[2]}")
        print(f"Количество арифметических итераций {result[3]}")
        print(f"Приближение: {F(result[0])}")
    print("----------------------------------------------------------------------")

def print_newton_method_full_mod():
    result = newton_method_full_mod()
    print("2.b")
    print("Нахождение решения системы нелинейных уравнений модифицированным методом Ньютона")
    if(result == False):
        print("ряд расходится")
    else:
        print(f"Решение {result[0]}")
        print(f"Затраченное время {result[1]}")
        print(f"Количество итераций {result[2]}")
        print(f"Количество арифметических итераций {result[3]}")
        print(f"Приближение: {F(result[0])}")
    print("----------------------------------------------------------------------")

def print_newton_method_k_mod(k):
    result = newton_method_k_mod(k)
    print("2.c")
    print(f"Нахождение решения системы нелинейных уравнений модифицированным методом Ньютона после {k} операции")
    if(result == False):
        print("ряд расходится")
    else:
        print(f"Решение {result[0]}")
        print(f"Затраченное время {result[1]}")
        print(f"Количество итераций {result[2]}")
        print(f"Количество арифметических итераций {result[3]}")
        print(f"Приближение: {F(result[0])}")
    print("----------------------------------------------------------------------")
    return result

def print_newton_method_hybrid_k(k):
    result = newton_method_hybrid_k(k)
    print("2.d")
    print(f"Нахождение решения системы нелинейных уравнений гибридным методом Ньютона c пересчётом после {k} операций")
    if(result == False):
        print("ряд расходится")
    else:
        print(f"Решение {result[0]}")
        print(f"Затраченное время {result[1]}")
        print(f"Количество итераций {result[2]}")
        print(f"Количество арифметических итераций {result[3]}")
        print(f"Приближение: {F(result[0])}")
    print("----------------------------------------------------------------------")
    return result

print_newton_method_root()
print_newton_method(x_0)
print_newton_method_full_mod()
print_newton_method_k_mod(3)
print_newton_method_hybrid_k(3)

print(f"\n\n\n")
print("x_0 - изменено")
x_0 = np.array([0.5, 0.5, 1.5, -1.0, -0.2, 1.5, 0.5, -0.5, 1.5, -1.5])
print_newton_method(x_0)
print_newton_method_full_mod()

min_op = 100000000000000000000000000
min_k = 0
for i in range(11):
    res = print_newton_method_k_mod(i)
    if(res != False):
        if(res[3] < min_op):
            min_k = i
            min_op = res[3]
print(f"оптимальное к в текущем случае: {min_k}")

min_op = 100000000000000000000000000
min_k = 0
for i in range(1,11):
    res = print_newton_method_hybrid_k(i)
    if(res != False):
        if(res[3] < min_op):
            min_k = i
            min_op = res[3]
print(f"оптимальное к в текущем случае: {min_k}")
