#pragma once

#include <reaction/reaction.h>

namespace test_reaction {

class IdTrackedFields : public reaction::FieldBase {
public:
    explicit IdTrackedFields(int value)
        : m_value(field(value)) {}

    reaction::Var<int> &valueField() { return m_value; }

private:
    reaction::Var<int> m_value;
};

struct FieldIdComparison {
    uint64_t firstIdFirstRead;
    uint64_t firstIdSecondRead;
    uint64_t secondId;
};

/**
 * Function: Compare FieldBase-generated IDs from different instances
 *
 * @param initialFirst Initial value for the first field container
 * @param initialSecond Initial value for the second field container
 * @return FieldIdComparison Snapshot of IDs for stability and uniqueness
 */
FieldIdComparison test_field_unique_id(int initialFirst, int initialSecond) {
    IdTrackedFields first(initialFirst);
    IdTrackedFields second(initialSecond);

    const uint64_t firstIdFirstRead = first.getId();
    const uint64_t firstIdSecondRead = first.getId();
    const uint64_t secondId = second.getId();

    // Touch reactive fields to avoid unused variable warnings
    first.valueField().value(initialFirst + 1);
    second.valueField().value(initialSecond + 1);

    return FieldIdComparison{
        .firstIdFirstRead = firstIdFirstRead,
        .firstIdSecondRead = firstIdSecondRead,
        .secondId = secondId,
    };
}

}  // namespace test_reaction


