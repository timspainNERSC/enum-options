#include "EnumWrapper.hpp"

using EnumWrap::EnumWrapper;

#include <iostream>
#include <map>
#include <boost/program_options.hpp>
namespace Nn {
class Cc {
public:
  enum class Farge {
    rød,
    grønn,
    blå
  };

  enum class Dyr {
    katt,
    fugl,
    pinnesvinne
  };
};
}

#define FARGE Nn::Cc::Farge
MAP_ENUM(FARGE,
	 {"red", FARGE::rød},
	 {"green", FARGE::grønn},
	 {"blue", FARGE::blå});
/*
template <>
const EnumWrapper<Nn::Cc::Farge>::MapType EnumWrapper<Nn::Cc::Farge>::map =
  { {"red", Nn::Cc::Farge::rød},
    {"green", Nn::Cc::Farge::grønn},
    {"blue", Nn::Cc::Farge::blå} };
*/

#define DYR Nn::Cc::Dyr
MAP_ENUM(DYR,
	 {"cat", DYR::katt},
	 {"bird", DYR::fugl},
	 {"hedgie", DYR::pinnesvinne});

int main(int argc, char** argv)
{
  std::string optName = "option.colour";

  boost::program_options::options_description opt("Enum test");
  opt.add_options()
    (optName.c_str(), boost::program_options::value<EnumWrapper<Nn::Cc::Farge>>(), "Specify a colour")
    ;
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::command_line_parser(argc, argv)
				.options(opt)
				.style(boost::program_options::command_line_style::unix_style)
				.allow_unregistered()
				.run()
				, vm);
  Nn::Cc::Farge colour = vm[optName].as<EnumWrapper<Nn::Cc::Farge>>();

  switch(colour) {
  case(Nn::Cc::Farge::rød):
    std::cout << "Red!" << std::endl;
    break;
  case(Nn::Cc::Farge::grønn):
    std::cout << "Green!" << std::endl;
    break;
  case(Nn::Cc::Farge::blå):
    std::cout << "Blue!" << std::endl;
    break;
  default:
    std::cout << "No colour found" << std::endl;
    break;
  }
  return 0;
}
