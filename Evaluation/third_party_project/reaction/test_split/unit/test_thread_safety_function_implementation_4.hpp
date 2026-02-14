

#include "../common/test_fixtures.h"
#include "../common/test_helpers.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

/**
 * Functional core for: ThreadSafetyTest.ThreadSafetyVerification
 *
 * @return tuple: (raceDetected, readCount, writeCount, tearingCount)
 */
std::tuple<bool, int, int, int> runThreadSafetyVerificationScenario() {
    auto &manager = reaction::ThreadManager::getInstance();
    manager.resetForTesting();

    struct TestData {
        int a;
        int b;
        TestData(int x = 0, int y = 0) : a(x), b(y) {}
        bool isValid() const { return a == b; } // valid if a == b
    };

    auto sharedVar = reaction::var(TestData(0, 0));
    std::atomic<bool> raceDetected{false};
    std::atomic<int> readCount{0};
    std::atomic<int> writeCount{0};
    std::atomic<int> tearingCount{0};

    // Writer
    auto writer = [&]() {
        for (int i = 1; i <= 5000; ++i) {
            try {
                TestData data(i, i);
                sharedVar.value(data);
                writeCount++;
                std::this_thread::sleep_for(std::chrono::nanoseconds(500));
            } catch (const std::exception &) {
                raceDetected = true;
            }
        }
    };

    // Reader
    auto reader = [&]() {
        for (int i = 0; i < 10000; ++i) {
            try {
                TestData data = sharedVar.get();
                readCount++;
                if (!data.isValid() && !(data.a == 0 && data.b == 0)) {
                    tearingCount++;
                    raceDetected = true;
                }
                std::this_thread::sleep_for(std::chrono::nanoseconds(250));
            } catch (const std::exception &) {
                raceDetected = true;
            }
        }
    };

    std::thread w1(writer);
    std::thread w2(writer);
    std::thread r1(reader);
    std::thread r2(reader);

    w1.join();
    w2.join();
    r1.join();
    r2.join();

    return {raceDetected.load(),
            readCount.load(),
            writeCount.load(),
            tearingCount.load()};
}

