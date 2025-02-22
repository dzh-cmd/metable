#include "common/logging.h"

#include <fstream>

#include "gtest/gtest.h"

TEST(LoggingTest, TestLogLevel) {
  metable::MetableLog::StartMetableLog(
      "log/test.log", metable::MetableLogLevel::RLL_INFO, 10, 3);
  METABLE_LOG(RLL_DEBUG) << "this debug message won't show up " << 456;
  METABLE_LOG(RLL_WARNING) << "Hello " << 123;
  METABLE_LOG(RLL_INFO) << "world " << 456 << " 789";
  METABLE_CHECK(true) << "This is a METABLE_CHECK"
                      << " message but it won't show up";
  metable::MetableLog::ShutDownMetableLog();
  std::fstream file("log/test.log");

  std::string line;
  uint8_t debug_count = 0;
  uint8_t info_count = 0;
  uint8_t warn_count = 0;
  while (getline(file, line)) {
    std::cout << "line:" << line << std::endl;
    if (line.find("debug") != std::string::npos) {
      debug_count++;
    } else if (line.find("info") != std::string::npos) {
      info_count++;
    } else if (line.find("warning") != std::string::npos) {
      warn_count++;
    }
  }

  ASSERT_EQ(debug_count, 0);
  ASSERT_EQ(info_count, 1);
  ASSERT_EQ(warn_count, 1);
  file.close();
  std::remove("log/test.log");
}

// Here tests trivial things for the logging
// TEST(LoggingTest, TestLogTrivial) {
//    metable::NodeID node_id;
//    METABLE_LOG(RLL_DEBUG) << node_id;
//}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
