#pragma once

#include <reaction/reaction.h>
#include <string>

namespace test_reaction {

// ============================================
// Data model definitions
// ============================================

class PersonRecord : public reaction::FieldBase {
public:
    PersonRecord(const std::string& name, int age)
        : m_name(field(name)), m_age(field(age)) {}

    std::string getName() const { return m_name.get(); }
    int getAge() const { return m_age.get(); }

    void setName(const std::string& name) { m_name.value(name); }
    void setAge(int age) { m_age.value(age); }

private:
    reaction::Var<std::string> m_name;
    reaction::Var<int> m_age;
};

// ============================================
// Function implementations
// ============================================

/**
 * Function: Test reactive fields updating calculated info
 *
 * @param initialName Initial person name
 * @param initialAge Initial person age
 * @param newName Updated person name
 * @param newAge Updated person age
 * @return std::string Concatenated info after updates
 */
std::string test_reactive_fields(const std::string& initialName,
                                 int initialAge,
                                 const std::string& newName,
                                 int newAge) {
    using namespace reaction;

    // Create a reactive person record
    auto person = var(PersonRecord{initialName, initialAge});

    // Create calculation depending on reactive fields
    auto infoCalc = calc([](const PersonRecord& p) {
        return p.getName() + "@" + std::to_string(p.getAge());
    }, person);

    // Update fields through reactive object
    person->setName(newName);
    person->setAge(newAge);

    // Return updated info
    return infoCalc.get();
}

}  // namespace test_reaction

