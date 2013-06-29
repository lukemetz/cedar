#pragma once
#include <sstream>

namespace cedar { namespace matchers { namespace stringifiers {
    std::string object_description_for(const void *objectValue);

    template<typename U>
    std::string string_for(const U & value) {
        std::stringstream output;
        output << value;
        return output.str().c_str();
    }
    
    inline std::string string_for(const char value) {
        return string_for(static_cast<const int>(value));
    }

    inline std::string string_for(const bool value) {
        return value ? "true" : "false";
    }

    inline std::string string_for(const std::nullptr_t ptr) {
      return "0x0";
    }
}}}
