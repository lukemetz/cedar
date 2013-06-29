#include <sstream>

#include "CedarStringifiers.h"

namespace cedar { namespace matchers {
    struct BaseMessageBuilder {
        template<typename U>
        static std::string string_for_actual_value(const U & value) {
            return stringifiers::string_for(value);
        }
    };

    /**
     * Basic functionality for all matchers.  Meant to be used as a convenience base class for
     * matcher classes.
     */
    template<typename MessageBuilder_ = BaseMessageBuilder>
    class Base {
    private:
        Base & operator=(const Base &);

    public:
        Base();
        virtual ~Base() = 0;
        // Allow default copy ctor.

        template<typename U>
        std::string failure_message_for(const U &) const;
        template<typename U>
        std::string negative_failure_message_for(const U &) const;

    protected:
        virtual std::string failure_message_end() const = 0;
    };

    template<typename MessageBuilder_>
    Base<MessageBuilder_>::Base() {}
    template<typename MessageBuilder_>
    Base<MessageBuilder_>::~Base() {}

    template<typename MessageBuilder_> template<typename U>
    std::string Base<MessageBuilder_>::failure_message_for(const U & value) const {
        std::string failureMessageEnd = this->failure_message_end();
        std::string actualValueString = MessageBuilder_::string_for_actual_value(value);
        return "Expected <" + actualValueString + "> to " + failureMessageEnd;
    }

    template<typename MessageBuilder_> template<typename U>
    std::string Base<MessageBuilder_>::negative_failure_message_for(const U & value) const {
        std::string failureMessageEnd = this->failure_message_end();
        std::string actualValueString = MessageBuilder_::string_for_actual_value(value);
        return "Expected <" + actualValueString + "> to not " + failureMessageEnd;
    }
}}
