namespace cedar { namespace matchers { namespace comparators {

#pragma mark Generic
    template<typename T, typename U>
    bool compare_equal(const T & actualValue, const U & expectedValue) {
      return actualValue == expectedValue;
    }
}}}
