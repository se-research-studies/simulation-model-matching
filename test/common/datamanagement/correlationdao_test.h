#pragma once

#include <gtest/gtest.h>

#include <FeatureSimulation/Common/DataManagement/CorrelationDAO>

class CorrelationDAOTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;

protected:
  Common::CorrelationDAO dao;
  std::string testCorFilenameBase = "test";
  std::string testCorFilename = testCorFilenameBase + ".cor";
};
