#include <boost/system/error_code.hpp>  // bring in boost::system::error_code et al
#include <iostream>
#include <string>  // for string printing
#include <filesystem>

// This is the custom error code enum
enum class Analysis_Error_Code
{
  Success = 0,  // 0 should not represent an error
  Python_Init_Fail = 1,
  Function_Parse_Fail = 2,
  Function_Execute_Error = 3,
  Script_Not_Found = 4

};

namespace boost
{
namespace system
{
// Tell the C++ 11 STL metaprogramming that enum Analysis_Error_Code
// is registered with the standard error code system
template <> struct is_error_code_enum<Analysis_Error_Code> : std::true_type
{
};
}  // namespace system
}  // namespace boost

namespace detail
{
// Define a custom error code category derived from boost::system::error_category
class Analysis_Error_Code_category : public boost::system::error_category
{
 public:
  // Return a short descriptive name for the category
  virtual const char *name() const noexcept override final { return "ConversionError"; }
  // Return what each enum means in text
  virtual std::string message(int c) const override final
  {
    switch(static_cast<Analysis_Error_Code>(c))
    {
      case Analysis_Error_Code::Success:
        return "conversion successful";
      case Analysis_Error_Code::Python_Init_Fail:
        return "Python_Init_Fail";
      case Analysis_Error_Code::Function_Parse_Fail:
        return "Function_Parse_Fail";
      case Analysis_Error_Code::Function_Execute_Error:
        return "Function Execute Error";
      case Analysis_Error_Code::Script_Not_Found:
        return "Script_Not_Found";
      default:
        return "unknown";
    }
  }
  // OPTIONAL: Allow generic error conditions to be compared to me
  virtual boost::system::error_condition default_error_condition(int c) const noexcept override final
  {
    switch(static_cast<Analysis_Error_Code>(c))
    {
      case Analysis_Error_Code::Python_Init_Fail:
        return make_error_condition(boost::system::errc::invalid_argument);
      case Analysis_Error_Code::Function_Parse_Fail:
        return make_error_condition(boost::system::errc::invalid_argument);
      case Analysis_Error_Code::Function_Execute_Error:
        return make_error_condition(boost::system::errc::result_out_of_range);
      default:
        // I have no mapping for this code
        return boost::system::error_condition(c, *this);
    }
  }
};
}  // namespace detail

// Define the linkage for this function to be used by external code.
// This would be the usual __declspec(dllexport) or __declspec(dllimport)
// if we were in a Windows DLL etc. But for this example use a global
// instance but with inline linkage so multiple definitions do not collide.
#define THIS_MODULE_API_DECL extern inline

// Declare a global function returning a static instance of the custom category
THIS_MODULE_API_DECL const detail::Analysis_Error_Code_category &Analysis_Error_Code_category()
{
  static detail::Analysis_Error_Code_category c;
  return c;
}


// Overload the global make_error_code() free function with our
// custom enum. It will be found via ADL by the compiler if needed.
inline boost::system::error_code make_error_code(Analysis_Error_Code e)
{
  return {static_cast<int>(e), Analysis_Error_Code_category()};
}

//int main(void)
//{
//  // Note that we can now supply Analysis_Error_Code directly to error_code
//  boost::system::error_code ec = Analysis_Error_Code::Function_Parse_Fail;
//
//  std::cout << "Analysis_Error_Code::Function_Parse_Fail is printed by boost::system::error_code as "
//            << ec << " with explanatory message " << ec.message() << std::endl;
//
//  // We can compare Analysis_Error_Code containing error codes to generic conditions
//  std::cout << "ec is equivalent to boost::system::errc::invalid_argument = "
//            << (ec == std::errc::invalid_argument) << std::endl;
//  std::cout << "ec is equivalent to boost::system::errc::result_out_of_range = "
//            << (ec == std::errc::result_out_of_range) << std::endl;
//  return 0;
//}