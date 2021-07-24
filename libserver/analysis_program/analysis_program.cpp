//
// Created by alittlehorse on 4/25/21.
//

#include <libserver/analysis_program/analysis_program.hpp>



//TODO:given an python program ,execute it and store result in the file
/// execute the program given in the input_path
/// if it run success, store the result in primary_input_path file
/// \return Result<string,error>
outcome::result<std::string> analysis_program::execute(string program_str,string primary_input_path) noexcept {
  Py_Initialize();
  if (!Py_IsInitialized())
  {
    return Analysis_Error_Code::Python_Init_Fail;
  }
  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
  string python_script_name = "analysis_execute_script";
  if(!filesystem::exists(python_script_name+".py")){
    char buffer[1000];
  getcwd(buffer, 1000);
  fprintf(stderr,"python script %s not found\n", (python_script_name + ".py").c_str());
  fprintf(stderr,"The current directory is: %s\n", buffer);

    return Analysis_Error_Code::Script_Not_Found;
  }
  PyObject * pModule = NULL;//声明变量
  PyObject * pFunc = NULL;// 声明变量

  pModule = PyImport_ImportModule("analysis_execute_script");

  if (pModule == NULL)
  {
    std::cout << "没找到" << std::endl;
  }

  pFunc = PyObject_GetAttrString(pModule, "execute");//这里是要调用的函数名
  PyObject* pRet = PyObject_CallFunction(pFunc,"s",program_str.c_str());
  //PyObject* pRet = PyObject_CallFunctionObjArgs(pFunc,args);//调用函数
  char* res;
  PyArg_Parse(pRet, "s", &res);//转换返回类型
  ofstream outfile;
  outfile.open(primary_input_path, ios_base::out | ios_base::trunc);  //删除文件重写
  outfile << res << endl;
  Py_Finalize();
  return string(res);
}