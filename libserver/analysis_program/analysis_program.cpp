//
// Created by alittlehorse on 4/25/21.
//

#include <libserver/analysis_program/analysis_program.hpp>

//TODO:given an python program ,execute it and store result in the file
/// execute the program given in the input_path
/// if it run success, store the result in file--result file
/// else return error;
/// \return Result<string,error>
std::string analysis_program::execute(string program_str) {
  Py_Initialize();
  if (!Py_IsInitialized())
  {
    printf("初始化失败！");
    return 0;
  }
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
//  char buffer[1000];
//  getcwd(buffer, 1000);
//  printf("The current directory is: %s", buffer);

  PyObject * pModule = NULL;//声明变量
  PyObject * pFunc = NULL;// 声明变量

  pModule = PyImport_ImportModule("analysis_execute_script");

  if (pModule == NULL)
  {
    std::cout << "没找到" << std::endl;
  }

  pFunc = PyObject_GetAttrString(pModule, "execute");//这里是要调用的函数名
  PyObject* args = Py_BuildValue("s",program_str.c_str());
  PyObject* pRet = PyObject_CallOneArg(pFunc,args);
  //PyObject* pRet = PyObject_CallFunctionObjArgs(pFunc,args);//调用函数
  char* res;
  PyArg_Parse(pRet, "s", &res);//转换返回类型
  cout << res;
  Py_Finalize();
  return "";
}