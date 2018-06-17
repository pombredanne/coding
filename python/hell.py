# print ("please input you code!\n")
# name=input()
# print (name)
import os
from functools import reduce
import functools
import types
import pdb
import logging
import pickle
import json
from multiprocessing import Process, Pool
import subprocess

logging.basicConfig(level=logging.INFO)
print("please input you code!\n")


def defaultargs(name, age, *, county, city):
    print(name, age, county, city)


def getCurrentFilename(path):
    filename_lists = [d for d in os.listdir(path)]
    print(filename_lists)


def listgen():
    L = ['Hello', 'World', 18, 'Apple', None]
    out = [s.lower() for s in L if isinstance(s, str)]
    print(out)


def int2str():
    return list(map(str, [i for i in range(10)]))


def main(name, age, **kw):
    defaultargs('jsk', '14', county='county', city='city')
    di = {'one': 1, 'two': 2, 'three': 3}
    for v in di.items():
        print(v)
    for v in di.values():
        print(v)
    lis = ['a', 'b', 'c']
    for i in enumerate(lis, 1):
        print(i)


def list2int():
    def fn(x, y):
        return x * 10 + y

    return reduce(fn, [1, 2, 3, 4, 5])


# def str2int():
# 	def fn(x,y):
# 		return x*10+y
# 	def char2num(s):
# 		DIGITS={'0':0,'1':1,'2':2,'3':3,'4':4,'5':5,'6':6,'7':7,'8':8,'9':9}
# 		return DIGITS[s]
# 	t=((map(char2num, "123456")))
# 	return reduce(fn, t)


def str2int():
    def fn(x, y):
        return x * 10 + y

    def char2num(s):
        DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4,
                  '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}
        return DIGITS[s]

    t = ((map(char2num, "123456")))
    return reduce(lambda x, y: x * 10 + y, map(char2num, "123456"))


def frimes_filter():
    def _odd_iter():
        n = 1
        while True:
            n = n + 1
            yield n

    def _not_prime(n):
        return lambda x: x % n > 0

    yield 2
    it = _odd_iter()
    while True:
        n = next(it)
        yield n
        it = filter(_not_prime(n), it)


def log(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        print('call %s():' % func.__name__)
        return func(*args, **kw)

    return wrapper


def log(text):
    def decorator(func):
        def wrapper(*args, **kw):
            print('%s %s():' % (text, func.__name__))
            return func(*args, **kw)

        return wrapper

    return decorator


@log("exec")
def getfrimes(n):
    list_frimes = []
    for i in frimes_filter():
        if i < n:
            list_frimes.append(i)
        else:
            break
    return list_frimes


def sorted_test():
    li = [1, 2, 5, 3, 9, 0]
    sorted(li, key=abs)  # key=str.lower()


def pick():
    d = dict(name='Bob', age=20, score=88)
    p = pickle.dumps(d)
    print(p)
    unpick = pickle.loads(p)
    print(unpick)
    print(json.dumps(d))


class Student(object):
    def __init__(self, name, age):
        self.__name = name
        self.__age = age

    def print_(self):
        print("you name is {name} \nyou age is {age}".format(name=self.__name, age=self.__age))

    def get_name(self):
        return self.__name

    def get_age(self):
        return self.__age


def process_test():
    def run_process(name):
        print('%s %d ' % (name, os.getpid()))

    p = Process(target=run_process, args=('test',))
    print('child process start.')
    p.start()
    p.join()
    print("child process end.")


def subprocess_test():
    r = subprocess.call(['nslookup', 'www.python.org'])
    p = subprocess.Popen(['nslookup'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


if __name__ == '__main__':
    main('jsk', '21', city='beijing')
    getCurrentFilename(".")
    listgen()
    print(int2str())
    print(list2int())
    str2int()
    (getfrimes(100))
    lambda n: n % 2 == 1
    int2 = functools.partial(int, base=2)
    stu1 = Student('jsk', '12')
    stu1.print_()
    stu1.get_age()
    # pdb.set_trace()  #stop here
    type('object')
    print(dir(stu1))
    a = 3
    logging.info(a)
    pick()
    process_test()
    # with open('/path/to/file', 'r') as f:  #auto exec f.close()
    #  print(f.read())
# for line in f.readlines():
#   	print(line.strip()) # 把末尾的'\n'删掉
# l look the code
# n next code
# p value   get the value of ...
