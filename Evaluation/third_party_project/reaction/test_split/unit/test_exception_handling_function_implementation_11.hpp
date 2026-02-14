

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Helper function that tries to access a closed variable.
 *
 * This is used to trigger a NullPointerAccessException in the framework.
 *
 * @return Whether a NullPointerAccessException was thrown.
 */
bool access_closed_variable_throws_null_pointer() {
    auto var1 = var(42);
    var1.close(); // Close the reactive node

    try {
        (void)var1.get();
        return false;
    } catch (const NullPointerAccessException&) {
        return true;
    }
}

