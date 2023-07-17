import numpy as np

def gram_shmidt(A):# ортоганиализация матрицы A методом Грама Шмита
    n = A.shape[0]
    Q = np.zeros((n, n))# создаём результирующую матрицу
    for i in range(0,n):
        Q[0:n, i] = A[0:n, i]# проходимся по всем её столбцам, изначально приравниваем к столбцам матрицы A
        for j in range(i):# проходимся по всем уже созданным столбцам матрицы Q
            kef = Q[0:n, i].dot(Q[0:n, j]) / Q[0:n, j].dot(Q[0:n, j]) #проекция i-того столбца матрицы A на j-тый столбец матрицы Q
            for k in range(n):
                Q[k, i] -= kef * Q[k, j]
    return Q

def normalization(Q):# просто делим каждый вектор матрыцы на его норму
    n = Q.shape[0]
    for i in range(0, n):
        Q[0:n, i] /= np.linalg.norm(Q[0:n, i])
    return Q

def QR_decomp(A):
    Q = gram_shmidt(A)# ортагонализируем матрицу
    Q = normalization(Q)# нормализуем
    R = Q.T @ A# получем верхнюю триуголную матрицу домножением обыяной на обратную ортогональную
    return (Q, R)

def solve_QR(A, b):# решение системы уравнений с помощью qr разложения
    (Q, R) = QR_decomp(A)# расскладываем
    x = np.linalg.inv(R) @ Q.T @ b# решеам домножив на обратные матрицы
    return x

def solve_check(matrix, b, x):# проверка решения
    check = matrix @ x - b
    for i in range(check.shape[0]):
        if check[i] > 0.00001:
            return False
    return True

def BigCheck(quantity, size):
    for i in range(quantity):
        check_matrix = np.random.randint(0,size=(size, size),high=1000)# генерируем случайную матрицу
        while np.linalg.det(check_matrix) == 0:
            check_matrix = np.random.randint(0,size=(size, size),high=1000)

        result_of_matrix = np.random.randint(0,size=(size, 1),high=1000)# генерируем случайный столбец ответов
        x = solve_QR(check_matrix, result_of_matrix)
        flag = solve_check(check_matrix, result_of_matrix, x)# проверяем
        if(flag == False):
            return False
    return True


print(BigCheck(100,5))