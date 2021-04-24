import sys
import typing

'''
def compute_function(x):
    return 1
'''
def getData() -> typing.List:
    """
    return server's data, default data is [1,2,3,4,5]
    server can freely modify this function and
    get data from any sources(database,csv,etc)
    :return: server's data
    """
    return [1,2,3,4,5]

if __name__ == '__main__':
    compute:[None,] = None
    compute_function:str = str(sys.argv[0])
    try:
        exec(compute_function)
    except Exception as ex:
        print("wrong when parsing compute_function!")
        print("Your input is {}" % compute_function)
        exit(1)

    if not compute:
        print("function 'compute' not set!")
        exit(1)
    else:
        data = getData()
        exec(compute(data))



