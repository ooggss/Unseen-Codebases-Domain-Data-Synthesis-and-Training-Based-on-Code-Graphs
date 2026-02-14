

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Try resetting a calc expression with a mismatched type.
 *
 * This function creates a calc node returning int and tries to reset it
 * with a lambda returning double.
 *
 * @return A string indicating which exception was thrown or if it succeeded:
 *         - "TypeMismatchException"
 *         - "ReactionException"
 *         - "std::exception"
 *         - "none" (if no exception thrown)
 *         - "unknown"
 */
std::string perform_real_type_mismatch_reset() {
    auto calc = reaction::calc([]() { return 42; }); // int return type

    try {
        calc.reset([]() { return 3.14; }); // double return type
        return "none";
    } catch (const TypeMismatchException &e) {
        (void)e;
        return "TypeMismatchException";
    } catch (const ReactionException &e) {
        (void)e;
        return "ReactionException";
    } catch (const std::exception &e) {
        (void)e;
        return "std::exception";
    } catch (...) {
        return "unknown";
    }
}

