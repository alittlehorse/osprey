from typing import *
import traceback
def execute(program_str:str) -> str:
    try:
        exec(program_str,globals())

        return str(fun([1,2,3]))
    except Exception as e:
        return traceback.format_exc()
def cmake_test_fun():
    return "sss"
if __name__ == "__main__":
    s =\
    """def fun(data):
        return 2
    """
    print(execute(s))
