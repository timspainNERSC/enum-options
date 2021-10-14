#ifndef ENUMWRAPPER_HPP
#define ENUMWRAPPER_HPP

#include <string>
#include <map>
#include <boost/program_options.hpp>

namespace EnumWrap {
template <typename E> class EnumWrapper;
template <typename E> std::istream& operator>>(std::istream&, EnumWrapper<E>&);

template<typename E>
class EnumWrapper {
public:

  typedef const std::map<std::string, E> MapType;
  void operator()(const std::string& key)
  {
    value = map.at(key);
  }
  operator E() const
  {
    return value;
  }

  static MapType map;
  
  friend std::istream& operator>><E>(std::istream& is, EnumWrapper<E>&);
private:
  E value;
};


template <typename E>
std::istream& operator>>(std::istream& is, EnumWrapper<E>& e)
{
  std::string tok;
  is >> tok;
  try {
    e(tok);
  } catch (const std::out_of_range& oor) {
    throw boost::program_options::validation_error(
						   boost::program_options::validation_error::invalid_option);
  }
  return is;
}

#define MAP_ENUM(etype, mapping...) template <> const EnumWrapper<etype>::MapType EnumWrapper<etype>::map = {mapping}

}

#endif //ndef ENUMWRAPPER_HPP
