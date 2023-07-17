import math
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

#19

def integralX0(limit1, limit2):
    return ((limit2 - a)**(1-α) - (limit1 - a)**(1-α)) / (1-α)

def integralX1(limit1, limit2):
    return ((limit2 - a)**(2-α) - (limit1 - a)**(2-α)) / (2-α)

def integralX2(limit1, limit2):
    return ((limit2 - a)**(3-α) - (limit1 - a)**(3-α)) / (3-α)

def integralX3(limit1, limit2):
    return ((limit2 - a)**(4-α) - (limit1 - a)**(4-α)) / (4-α)

def integralX4(limit1, limit2):
    return ((limit2 - a)**(5-α) - (limit1 - a)**(5-α)) / (5-α)

def integralX5(limit1, limit2):
    return ((limit2 - a)**(6-α) - (limit1 - a)**(6-α)) / (6-α)


a = 1.1
b = 2.3
α = 2/5
β = 0
true_value = 8.565534222407634006755741863827588778916

def f(x):
    return 0.5*math.cos(3*x)*math.exp(2*x/5)+4*math.sin(3.5*x)*math.exp(-3*x) + 3*x

def midpoint_rule(f, a, b, step):
    n = round((b-a)/step)
    integral = 0
    for i in range(n):
        x = a + (i + 0.5) * step
        height = f(x)
        integral += height * step
    return integral

def Nuiton_Kots(f, a, b, step):
    limit1 = a
    limit2 = limit1 + step
    result = 0
    n = round((b-a)/step)
    for i in range(n):
        moments = [0]*3

        moments[0] = integralX0(limit1, limit2)
        moments[1] = integralX1(limit1, limit2) + a*moments[0]
        moments[2] = integralX2(limit1, limit2) + 2*a* moments[1] - a*a*moments[0]

        nodes = [0]*3

        nodes[0] = limit1
        nodes[1] = (limit2 + limit1)/2
        nodes[2] = limit2


        sol_koef = np.zeros((3,3))

        sol_koef[0, 0] = 1
        sol_koef[0, 1] = 1
        sol_koef[0, 2] = 1
        sol_koef[1, 0] = nodes[0]
        sol_koef[1, 1] = nodes[1]
        sol_koef[1, 2] = nodes[2]
        sol_koef[2, 0] = nodes[0]*nodes[0]
        sol_koef[2, 1] = nodes[1]*nodes[1]
        sol_koef[2, 2] = nodes[2]*nodes[2]

        koff_A = system_solution_LU(LU(sol_koef), moments)[0]

        result += koff_A[0]*f(nodes[0]) + koff_A[1]*f(nodes[1]) + koff_A[2]*f(nodes[2])

        limit1 += step
        limit2 += step
    return result

def Gauss(f, a, b, step):
    limit1 = a
    limit2 = limit1 + step
    result = 0
    n = round((b-a)/step)
    for i in range(n):
        moments = [0]*6

        moments[0] = integralX0(limit1, limit2)
        moments[1] = integralX1(limit1, limit2) + a*moments[0]
        moments[2] = integralX2(limit1, limit2) + 2*a*moments[1] - a**2*moments[0]
        moments[3] = integralX3(limit1, limit2) + 3.*a*moments[2] - 3*a**2*moments[1] + a**3*moments[0]
        moments[4] = integralX4(limit1, limit2) + 4.*a*moments[3] - 6*a**2*moments[2] + 4*a**3*moments[1] - a**4*moments[0]
        moments[5] = integralX5(limit1, limit2) + 5.*a*moments[4] - 10*a**2*moments[3] + 10*a**3*moments[2] - 5*a**4*moments[1] + a**5*moments[0]


        sol_koef = np.zeros((3,3))

        sol_koef[0, 0] = moments[0]
        sol_koef[0, 1] = moments[1]
        sol_koef[0, 2] = moments[2]
        sol_koef[1, 0] = moments[1]
        sol_koef[1, 1] = moments[2]
        sol_koef[1, 2] = moments[3]
        sol_koef[2, 0] = moments[2]
        sol_koef[2, 1] = moments[3]
        sol_koef[2, 2] = moments[4]

        sol_vec = np.zeros(3)

        sol_vec[0] = -moments[3]
        sol_vec[1] = -moments[4]
        sol_vec[2] = -moments[5]

        koff_a = system_solution_LU(LU(sol_koef), sol_vec)[0]

        nodes = np.roots([1, koff_a[2], koff_a[1], koff_a[0]])

        nodes = np.sort(nodes)

        sol_koef[0, 0] = 1
        sol_koef[0, 1] = 1
        sol_koef[0, 2] = 1
        sol_koef[1, 0] = nodes[0]
        sol_koef[1, 1] = nodes[1]
        sol_koef[1, 2] = nodes[2]
        sol_koef[2, 0] = nodes[0]*nodes[0]
        sol_koef[2, 1] = nodes[1]*nodes[1]
        sol_koef[2, 2] = nodes[2]*nodes[2]

        koff_A = system_solution_LU(LU(sol_koef), ([moments[0], moments[1], moments[2]]))[0]

        for j in range(3):
            result += koff_A[j]*f(nodes[j])

        limit1 += step
        limit2 += step
    return result

print('Метод прямоугольников')
print('__________________________________________________________________________')
step = (b-a)/1000
print(f'шаг - {step}')
integral = midpoint_rule(f,a,b,step)
print(f'реальная ошибка - {true_value - integral}')
print(f'значение - {integral}')

print('\n\n\nНьютон — Котс')
print('__________________________________________________________________________')
print('количество шагов - 2')

integral = Nuiton_Kots(f, a, b, (b-a)/2)
metodic_err = 1.07333333
error = true_value-integral
print(f'методическая ошибка - {metodic_err}')
print(f'реальная ошибка - {error}')
print(f'значение - {integral}')

print('__________________________________________________________________________')
print('Динамическое уменьшение шага, пока ошибка не станет меньше 10-6e')
error = 1
step = (b-a)
result2 = Nuiton_Kots(f,a,b,step)
step /= 2
result3 = Nuiton_Kots(f,a,b,step)
step /= 2
speed = 1

while(abs(error) > 1e-6):
    result1 = result2
    result2 = result3
    result3 = Nuiton_Kots(f,a,b,step)
    step /= 2
    speed = -math.log(abs((result3-result2)/(result2-result1)))/math.log(2)
    error = (result3 - result2)/(2**speed - 1)
    print(f'ошибка - {error}')
    print(f'скорость сходимости по Эйтикену - {speed}')

print(f'результат - {result3}')
print(f'реальная ошибка - {true_value - result3}')

print('__________________________________________________________________________')
print('Динамическое уменьшение шага, начиная с шага (b-a), пока ошибка не станет меньше 10-6e')
error = 1
step = (b-a)
step1 = step
result1 = Nuiton_Kots(f,a,b,step)
step /= 2
result2 = Nuiton_Kots(f,a,b,step)
error = (result2 - result1)/(2**3 - 1)
step_opt = step*pow(1e-6/abs(error), 1/3)
nopt = np.ceil((b-a)/step_opt)
step_opt = (b-a)/nopt
print(f'оптимальный шаг - {step_opt}')
result2 = Nuiton_Kots(f,a,b,step_opt)

while(abs(error) > 1e-6):
    result1 = result2
    step_opt /= 2
    result2 = Nuiton_Kots(f,a,b,step_opt)
    error = (result2 - result1)/(2**4 - 1)
    print(error)

print(f'результат - {result2}')
print(f'реальная ошибка - {true_value - result2}')

print('\n\n\nГаусс')
print('__________________________________________________________________________')
print('количество шагов - 2')

integral = Gauss(f, a, b, (b-a)/2)
metodic_err = 1.07333333
error = true_value-integral
print(f'методическая ошибка - {metodic_err}')
print(f'реальная ошибка - {error}')
print(f'значение - {integral}')

print('__________________________________________________________________________')
print('Динамическое уменьшение шага, пока ошибка не станет меньше 10-6e')
error = 1
step = (b-a)
result2 = Gauss(f,a,b,step)
step /= 2
result3 = Gauss(f,a,b,step)
step /= 2
speed = 1

while(abs(error) > 1e-6):
    result1 = result2
    result2 = result3
    result3 = Gauss(f,a,b,step)
    step /= 2
    speed = -math.log(abs((result3-result2)/(result2-result1)))/math.log(2)
    error = (result2 - result1)/(2**speed - 1)
    print(f'скорость сходимости по Эйтикену - {speed}')

print(f'результат - {result3}')
print(f'реальная ошибка - {true_value - result3}')

print('__________________________________________________________________________')
print('Динамическое уменьшение шага, начиная с шага (b-a), пока ошибка не станет меньше 10-6e')
error = 1
step = (b-a)
step1 = step
result1 = Gauss(f,a,b,step)
step /= 2
result2 = Gauss(f,a,b,step)
error = (result2 - result1)/(2**6 - 1)
step_opt = step1*pow(1e-6/abs(error), 1/6)
print(f'оптимальный шаг - {step_opt}')

while(abs(error) > 1e-6):
    result1 = result2
    result2 = Gauss(f,a,b,step_opt)
    step_opt /= 2
    error = (result2 - result1)/(2**4 - 1)
    print(error)

print(f'результат - {result2}')
print(f'реальная ошибка - {true_value - result2}')