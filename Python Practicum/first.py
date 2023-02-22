print( 'Hello world' )          # Вывод на экран
print( 2**5 )                   # Возведение в степень
print( 20 // 6 )                # Целочисленное деление

print("one" + "two")
print("spam" * 3)

user = "Name"
age = 42

x = 123.456                 
x = "This is a string now!"     # Переменные не имеют типа в питоне

x = input()                     # Ввод
st = input("Input new str:")    # Выводит строку пользователю

age = int(input())              # Строка -> int
str(age)                        # int -> Строка

print(num := int(input()))      # Присвоение еще "не существующего" значения :=

if 1 > 2:                       # Конструкция if
    # Текст инструкций
    print(0)
else:                           # Конструкция else
    print(1)

if True:                        # Конструкция elif
    print(1)
elif False:
    print(0)

print(1 == 1 and 2 == 2 or 3 != 5)      # and or

words = ["Hello", "world", "!", "New Line", "word"]     # Списки - создаются с помощью []
print(words[1:2])                                       # Интервал 
print(words[:2])                                        # С начала списка 
print(words[1:])                                        # До конца списка
print(words[1:4:2])                                     # Шаг (третий параметр)

empty_list = []                 # Пустой список

number = 3
things = ["string", 0, [1, 2, number], 4.56]    # Типы элементов в списке могут быть разные
print(things[1])
print(things[2])
print(things[2][2])

print("string" in things)       # Проверить наличие элемента в списке
things.append(4)                # Добавление элемента в список
print(len(things))              # Количество элементов списка
things.insert(1, "in [1]")      # Добавить элемент на нужную позицию в список
print(things.index(0))          # Вывод первого упоминания элемента в списке

i = 0
while i < 1:                    # While
    print(0)
    i += 1

for n in things:                # for
    print(n)

for x in "abcd":
    print(x)

numbers1 = list(range(3, 8))        # range на [3, 8)
numbers2 = list(range(10))          # range на [0, 10)
numbers3 = list(range(0, 10, 2))    # range с шагом последовательности 2

print(numbers1)
print(numbers2)
print(numbers3)

for i in range(5):                  # range в цикле
    print(i)


def my_func():                      # Функция
    print("spam")

my_func()

word = "example"
def my_print(word):
    print(word + "!")

my_print(word)

def op():                       # Функции как переменные
    return "MY_OP FUNCTION"

my_op = op
print(my_op())

import random                           # Модуль
from math import pi                     # Элемент из модуля
from math import sqrt as square_root    # Элемент из модуля с переименованием



try:
    print(1/0)
except ZeroDivisionError:
    print("/ 0")
except (TypeError, ValueError):
    print("Error")
finally:
    print("i'm here lol")

#raise ValueError                   # Вызов исключений


print("AAAAAAAAAAAAAAAAAA")
myfile = open("/Users/2lapsha1/python_learn/in.txt")             # Открытие файла

"""
Режимы файлов:
open("filename.txt", "r")  - Чтение - по умолчанию
open("filename.txt", "w")  - Запись
open("filename.txt", "a")  - Добавление в конец
open("filename.txt", "wb") - бинарная запись
"""

cont = myfile.read()                # содержимое файла
#print(cont)
print(myfile.read(4))               # Чтение количества байт
print(myfile.readlines())           # Возвращает список, где каждый элемент - каждая строка файла

myfile.close()                      # Закрытие файлов

try:                                                    # Отладка открытия файла
    file = open("newfile.txt", "w")                     # Запись в файл
    file.write("This has been written to a file")       # write возвращает количество байт, запианных в файл
finally:
    file.close()

with open("in.txt") as f:
    print(f.read())

ages = {"Dave": 24, "Mary": 42, "John": 58}             # Словарь - задается с помощью {}
print(ages["Dave"])
print(ages["Mary"])

print("Dave" in ages)
print("Mark" in ages)

words = ("one", "two", "three")                         # Кортеж - задается с помощью ()


class Example:                                          # Класс
    def __init__ (self, param1, param2):
        self.param1 = param1
        self.param2 = param2
    def func(self):
        print("Hello")


fido = Example("Fido", "brown")
print(fido.param1)
fido.func()

