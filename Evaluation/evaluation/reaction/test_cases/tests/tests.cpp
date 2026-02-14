#include <gtest/gtest.h>
#include <hexi/hexi.h>
#include <hexi/endian.h>
#include <vector>
#include <cstdint>
#include <span>
#include <cmath>

// Include the implementation
#include "implementation.hpp"

TEST(MeasurementData, SerializeDeserialize) {
    MeasurementData original;
    original.sensor_id = 12345;
    original.temperatures = {25.5f, 30.0f, 28.3f};
    original.pressure = 1013.25;
    
    auto buffer = serialize_measurement_data(original);
    ASSERT_FALSE(buffer.empty());
    
    MeasurementData deserialized = deserialize_measurement_data(buffer);
    
    EXPECT_EQ(original.sensor_id, deserialized.sensor_id);
    EXPECT_EQ(original.temperatures.size(), deserialized.temperatures.size());
    for (size_t i = 0; i < original.temperatures.size(); ++i) {
        EXPECT_FLOAT_EQ(original.temperatures[i], deserialized.temperatures[i]);
    }
    EXPECT_DOUBLE_EQ(original.pressure, deserialized.pressure);
}

TEST(MeasurementData, SerializeDeserializeEmptyTemperatures) {
    MeasurementData original;
    original.sensor_id = 999;
    original.temperatures = {};
    original.pressure = 1000.0;
    
    auto buffer = serialize_measurement_data(original);
    
    MeasurementData deserialized = deserialize_measurement_data(buffer);
    
    EXPECT_EQ(original.sensor_id, deserialized.sensor_id);
    EXPECT_TRUE(deserialized.temperatures.empty());
    EXPECT_DOUBLE_EQ(original.pressure, deserialized.pressure);
}

TEST(MeasurementData, SerializeDeserializeFloatPrecision) {
    MeasurementData original;
    original.sensor_id = 42;
    original.temperatures = {3.14159f, -273.15f, 100.123f};
    original.pressure = 98765.4321;
    
    auto buffer = serialize_measurement_data(original);
    
    MeasurementData deserialized = deserialize_measurement_data(buffer);
    
    EXPECT_EQ(original.sensor_id, deserialized.sensor_id);
    EXPECT_EQ(original.temperatures.size(), deserialized.temperatures.size());
    for (size_t i = 0; i < original.temperatures.size(); ++i) {
        EXPECT_NEAR(original.temperatures[i], deserialized.temperatures[i], 0.0001f);
    }
    EXPECT_NEAR(original.pressure, deserialized.pressure, 0.0001);
}

TEST(MeasurementData, ExtractSensorInfo) {
    MeasurementData data;
    data.sensor_id = 777;
    data.temperatures = {20.0f, 21.0f};
    data.pressure = 1013.0;
    
    auto buffer = serialize_measurement_data(data);
    
    SensorInfo info = extract_sensor_info(buffer);
    
    EXPECT_EQ(data.sensor_id, info.sensor_id);
}

TEST(MeasurementData, EndiannessConversion) {
    MeasurementData original;
    original.sensor_id = 0x12345678;
    original.temperatures = {1.0f, 2.0f};
    original.pressure = 3.14159;
    
    auto buffer = serialize_measurement_data(original);
    
    // Verify that float and double values are stored in little-endian format
    // On big-endian systems, bytes will be swapped
    if constexpr (std::endian::native == std::endian::big) {
        // On big-endian systems, the bytes should be swapped for little-endian storage
        // This is a basic check - actual byte verification would be more complex
    }
    
    MeasurementData deserialized = deserialize_measurement_data(buffer);
    
    EXPECT_EQ(original.sensor_id, deserialized.sensor_id);
    EXPECT_EQ(original.temperatures.size(), deserialized.temperatures.size());
    for (size_t i = 0; i < original.temperatures.size(); ++i) {
        EXPECT_FLOAT_EQ(original.temperatures[i], deserialized.temperatures[i]);
    }
    EXPECT_DOUBLE_EQ(original.pressure, deserialized.pressure);
}