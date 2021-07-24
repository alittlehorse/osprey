from typing import *
import traceback
def execute(program_str:str) -> str:
    program_str = program_str.strip()
    try:
        exec(program_str,globals())

        return str(fun([2,4,6,8,10]))
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
