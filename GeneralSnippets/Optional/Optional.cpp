// =====================================================================================
// std::optional
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <optional>

namespace Optional {

    class Contact
    {

    private:
        std::optional<std::string> m_homePhone;
        std::optional<std::string> m_workPhone;
        std::optional<std::string> m_mobilePhone;

    public:
        Contact() : 
            m_homePhone(std::nullopt),
            m_workPhone(std::nullopt),
            m_mobilePhone(std::nullopt) {}

        void addMobilePhone(std::string mobilePhone) {
            m_mobilePhone = mobilePhone;
        }

        std::optional<std::string> isPhoneNumberCorrect (std::string s)
        {
            // try to verify that given string describes valid phone number;
            // return "nothing" if test fails

            // if s contains valid phone number
            if (true)
                return { s };

            // "trailing return type deduction"
            return std::nullopt;
            // or
            return { };
        }

        std::optional<std::string> lookupPhoneNumber(std::string name)
        {
            // search name in internal list of phone book
            if (true)
                return { m_mobilePhone };

            // trailing return type dedection
            return std::nullopt;
            // or
            return { };
        }
    };

    void test_01_optional() {

        Contact myContact;
        myContact.addMobilePhone("123456789");

        std::optional<std::string> phone = myContact.lookupPhoneNumber("Hans");

        if (phone.has_value()) {
            std::cout << "Hans => " << phone.value() << "\n";
        }
        else {
            std::cout << "Hans not found!" << "\n";
        }
    }
}

void main_optional()
{
    using namespace Optional;
    test_01_optional();
}

// =====================================================================================
// End-of-File
// =====================================================================================