import pymongo
import serial
import datetime
# подключаемся к базе данных
db_client = pymongo.MongoClient("mongodb://localhost:27017/")
db = db_client["CardReader"]
names = db["names"]
action = db["action"]


port = serial.Serial('COM3', 9600, timeout=0.1)# подключаемся к порту
while True:
    string = port.readline().decode()# считываем порт
    if (len(string) == 0): # пропускаем если сигнал нулевой
        continue
    elif(string[0:2] == "SR"):# регестрируем карту
        print("Enter your name")
        key = string[3:len(string)-2]
        name = input()# считываем имя
        names.insert_one({"id":key, "name":name}) # добавляем имя в бд
        print("Your card susessfully registred")
    elif (string[0:2] == "AR"):# карта уже заригестрированна ничего не делаем
        print("Your card have been alredy registred")
    elif (string[0:2] == "SD"):# удаляем метку
        key = string[3:len(string) - 2]
        name = names.find_one({"id": key})["name"]# находим имя по ключю в бд
        names.delete_one({"id":key})# удаляем карту из бд
        action.delete({"name": name})# удаляем все действия по этой метке
        out = name + ",your card have been susessfully deleted"
        print(out)
    elif (string[0:2] == "NR"):# карта не зарегестрированна, ничего не делаем
        print("Your card is not registred")
    elif (string[0:2] == "NF"):#карта не найдена, ничего не делаем
        print("Your card is not founded")
    elif (string[0:2] == "AD"):
        names.delete_many({})# удаляем все элементы из бд
        action.delete_many({})
        print("All card have been delited")
    elif (string[0:2] == "AO"):
        all = action.find({})# находим все проходы
        for elements in all:
            print(elements["name"], elements["time"])#выводим их
    elif(string[0] == "F"):# карта найдена
        key = string[2:len(string)-2]
        name = names.find_one({"id":key})["name"]# находи имя в бд по ключю
        action.insert_one({"time": datetime.datetime.now(), "name": name})  # добавляем время и пользователя в бд
        out = name + ",you can pass   time:" + str(datetime.datetime.now().hour)+ " " + str(datetime.datetime.now().minute)#выводим имя пользователя и текущее время
        print(out)

