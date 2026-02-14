

#include <reaction/reaction.h>

using namespace reaction;

/**
 * @brief Create a simple dependency cycle to test actual cycle detection.
 *
 * This function constructs a variable and a calculation, then attempts to
 * reset the calculation in a way that creates a cycle.
 *
 * @return A string indicating which type of exception was actually thrown.
 *         Possible values:
 *         - "DependencyCycleException"
 *         - "ReactionException"
 *         - "std::exception"
 *         - "unknown"
 */
std::string perform_real_dependency_cycle_detection() {
    auto a = var(10);
    auto calc = reaction::calc([&]() { return a() + 1; });

    try {
        calc.reset([&]() { return calc() + a(); });
        return "none";
    } catch (const DependencyCycleException &e) {
        (void)e;
        return "DependencyCycleException";
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

