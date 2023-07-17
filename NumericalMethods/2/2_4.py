import numpy as np
import math
import warnings

warnings.filterwarnings('ignore')

def ItrTransformation(A, b):# перевод уравнения в вид: x = Bx + c
    n = A.shape[0]
    A_ = np.zeros((n,n),dtype='float64')# матрица B
    b_ = np.zeros(n, dtype='float64')# вектор столбец с
    for i in range(n):# далее просто расставляю значения в соответсвии с коэфицентами
        b_[i] = b[i] / A[i][i]
    for i in range(n):
        for j in range(n):
            if(i == j):
                A_[i][j] = 0
            else:
                A_[i][j] = -A[i][j]/A[i][i]
    return (A_, b_)

def Jacobi(A, b, eps):# метод Якоби
    n = A.shape[0]
    cur_eps = eps + 1 # разница между знацениями в предыдущей и текущей итерации
    (B, c) = ItrTransformation(A,b) # преобразовываем
    X_result = np.array([0.0]*n, dtype='float64')
    q = np.linalg.norm(B, ord=np.inf)
    c_norm = np.linalg.norm(c, ord=np.inf)
    if(q < 1):# если количество итераций оценимо заранее, оцениваем
        apriorEstimate = math.ceil(math.log(eps/c_norm * (1-q)) / math.log(q))# просто формула
    else:
        apriorEstimate = 0

    number_of_iteration = 0
    while cur_eps > eps * (1-q) / q:
        X_result_past = X_result.copy()# сохраняем значение x в пердидущей итерации
        X_result = np.dot(B, X_result_past) + c# вычисляем значение x в текущей итерации
        number_of_iteration += 1
        arr_eps = abs(X_result - X_result_past)# вычисляем разницу между итерациями
        cur_eps = max(arr_eps)
        if number_of_iteration == 1000:
            return False
    return (X_result, apriorEstimate, number_of_iteration)

def Seidel(A, b, eps):# метод Зейдоля
    n = A.shape[0]# то же самое что в предидущем методе
    cur_eps = eps + 1
    (B, c) = ItrTransformation(A,b)
    X_result = np.array([0.0]*n, dtype='float64')
    q = np.linalg.norm(B, ord=np.inf)
    c_norm = np.linalg.norm(c, ord=np.inf)
    if(q < 1):# если количество итераций оценимо заранее, оцениваем
        apriorEstimate = math.ceil(math.log(eps/c_norm * (1-q)) / math.log(q))# просто формула
        eps1 = eps * (1-q) / q
    else:
        apriorEstimate = 0
        eps1 = eps * 1e-2

    number_of_iteration = 0
    while cur_eps > eps1:
        X_result_past = X_result.copy()
        for i in range(n):# то же самое что в прошлом методе только, теперь мы используем только что вычисленное значение x
            X_result[i] = c[i]
            for j in range(n):
                X_result[i] += B[i][j] * X_result[j]
        number_of_iteration += 1
        arr_eps = abs(X_result - X_result_past)
        cur_eps = max(arr_eps)
        if number_of_iteration == 100000:
            return False

    return (X_result, apriorEstimate, number_of_iteration)

def DiagDominMatrGener(size):# генератор матрицы с диагональной доминацией
    check_matrix = np.random.randint(0,size=(size, size),high=100)# генерируем случайную матрицу
    while np.linalg.det(check_matrix) == 0:
        check_matrix = np.random.randint(0,size=(size, size),high=100)
    n = check_matrix.shape[0]
    for i in range(n):
        for j in range(n):
            if(i != j):
                check_matrix[i, i] += abs(check_matrix[i, j])# прибавлеем все мтрочные элементы к диагональному элементу, чтобы создать диагональную доминацию
    return check_matrix

def IsDiagDominMat(A):# проверка матрицы на диагональную доминацию
    n = A.shape[0]
    for i in range(n):
        diag_el = A[i][i]
        for j in range(n):
            if(i != j):
                diag_el -= A[i][j]
        if(diag_el < 0):
            return False
    return True

def IsPosDef(x):# проверка на положительность матрицы
    return np.all(np.linalg.eigvals(x) > 0)

def PosNonDiagDomMatGen(size):# генерируем положительную матрицу без диагональной доминации
    check_matrix = np.random.randint(0,size=(size, size),high=100)
    #while ((np.linalg.det(check_matrix) == 0) and (IsDiagDominMat(check_matrix)) and (IsPosDef(check_matrix))):
    #    check_matrix = np.random.randint(0,size=(size, size),high=100)
    return check_matrix @ check_matrix.T

def AnwserGen(size):# генерируем ветор ответов
    anwser = np.random.randint(0,size=(size, 1),high=100)
    return anwser

# проверяем
n = 3
diag = DiagDominMatrGener(n)
pol = PosNonDiagDomMatGen(n)
anwser_1 = AnwserGen(n)
anwser_2 = AnwserGen(n)
anwser_3 = AnwserGen(n)
anwser_4 = AnwserGen(n)

sol1, _, _ = Jacobi(diag, anwser_1, 0.000001)
print(Jacobi(diag, anwser_1, 0.000001))
print(np.linalg.solve(diag,anwser_1).T -sol1)
print(Jacobi(pol, anwser_2, 0.000001))

print(Seidel(diag, anwser_1, 0.000001))
print(Seidel(pol, anwser_2, 0.000001))
