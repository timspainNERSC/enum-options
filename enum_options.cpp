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
  } colour;

  enum class Dyr {
    katt,
    fugl,
    pinnesvinne
  };
};
}

typedef Nn::Cc::Farge FEnum;
typedef Nn::Cc::Dyr DEnum;


int main(int argc, char** argv)
{
  std::string optName = "option.colour";
  EnumWrapper<FEnum>::setMap({
      {"red", FEnum::rød},
      {"green", FEnum::grønn},
      {"blue", FEnum::blå}
  });
  std::string dyrNavn = "option.animal";
  EnumWrapper<DEnum>::setMap({
	 {"cat", DEnum::katt},
	 {"bird", DEnum::fugl},
	 {"hedgie", DEnum::pinnesvinne}
    });


  boost::program_options::options_description opt("Enum test");
  opt.add_options()
    (optName.c_str(), boost::program_options::value<EnumWrapper<FEnum>>(), "Specify a colour")
    (dyrNavn.c_str(), boost::program_options::value<EnumWrapper<DEnum>>(), "Choose an animal")
    ;
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::command_line_parser(argc, argv)
				.options(opt)
				.style(boost::program_options::command_line_style::unix_style)
				.allow_unregistered()
				.run()
				, vm);

  Nn::Cc fd;
  fd.colour = vm[optName].as<EnumWrapper<FEnum>>();

  switch(fd.colour) {
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

  switch(vm[dyrNavn].as<EnumWrapper<DEnum>>()) {
  case(DEnum::katt):
    std::cout << "Miaow!" << std::endl;
    break;
  case(DEnum::fugl):
    std::cout << "Ronk!" << std::endl;
    break;
  case(DEnum::pinnesvinne):
    std::cout << "Snuffle!" << std::endl;
    break;
  default:
    std::cout << "Nothing is heard" << std::endl;
  }
  return 0;
}
