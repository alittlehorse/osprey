#include <iostream>
#include <string>        // for string printing
#include <system_error>  // bring in std::error_code et al

// This is the custom error code enum
enum class Analysis_Error_Code {
  Success     = 0, // 0 should not represent an error
  Python_Init_Error = 1,
  Function_Parsing_Error = 2,
  Function_Executing_Error = 3,
};

namespace std
{
// Tell the C++ 11 STL metaprogramming that enum Analysis_Error_Code
// is registered with the standard error code system
template <> struct is_error_code_enum<ConversionErrc> : true_type
{
};
}

namespace detail
{
// Define a custom error code category derived from std::error_category
class ConversionErrc_category : public std::error_category
{
 public:
  // Return a short descriptive name for the category
  virtual const char *name() const noexcept override final
  { return "Analysis_Error_Code"; }
  // Return what each enum means in text
  virtual std::string message(int c) const override final
  {
    switch (static_cast<Analysis_Error_Code>(c))
    {
      case Analysis_Error_Code::Success:
        return "user's program runs successfully";
      case Analysis_Error_Code::Python_Init_Error:
        return "can't initialize python environment by Py_Initialize()";
      case Analysis_Error_Code::Function_Parsing_Error:
        return "can't parsing user's function";
      case Analysis_Error_Code::Function_Executing_Error:
        return "error when executing user's function";
      default:
        return "unknown condition in Analysis_Error_Code";
    }
  }
  // OPTIONAL: Allow generic error conditions to be compared to me
  virtual std::error_condition default_error_condition(int c) const noexcept override final
  {
    switch (static_cast<Analysis_Error_Code>(c))
    {
      case Analysis_Error_Code::Python_Init_Error:
        return make_error_condition(std::errc::invalid_argument);
      case Analysis_Error_Code::Function_Parsing_Error:
        return make_error_condition(std::errc::invalid_argument);
      case Analysis_Error_Code::Function_Executing_Error:
        return make_error_condition(std::errc::result_out_of_range);
      default:
        // I have no mapping for this code
        return std::error_condition(c, *this);
    }
  }
};
}

// Define the linkage for this function to be used by external code.
// This would be the usual __declspec(dllexport) or __declspec(dllimport)
// if we were in a Windows DLL etc. But for this example use a global
// instance but with inline linkage so multiple definitions do not collide.
#define THIS_MODULE_API_DECL extern inline

// Declare a global function returning a static instance of the custom category
THIS_MODULE_API_DECL const detail::ConversionErrc_category &ConversionErrc_category()
{
  static detail::ConversionErrc_category c;
  return c;
}


// Overload the global make_error_code() free function with our
// custom enum. It will be found via ADL by the compiler if needed.
inline std::error_code make_error_code(ConversionErrc e)
{
  return {static_cast<int>(e), ConversionErrc_category()};
}

int main(void)
{
  // Note that we can now supply Analysis_Error_Code directly to error_code
  std::error_code ec = Analysis_Error_Code::Function_Parsing_Error;

  std::cout << "Analysis_Error_Code::Function_Parsing_Error is printed by std::error_code as "
            << ec << " with explanatory message " << ec.message() << std::endl;

  // We can compare Analysis_Error_Code containing error codes to generic conditions
  std::cout << "ec is equivalent to std::errc::invalid_argument = "
            << (ec == std::errc::invalid_argument) << std::endl;
  std::cout << "ec is equivalent to std::errc::result_out_of_range = "
            << (ec == std::errc::result_out_of_range) << std::endl;
  return 0;
}