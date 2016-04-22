#pragma once

#include <gtest/gtest.h>

#include <FeatureSimulationCommon/DataManagement/CorrelationDAO>

class CorrelationDAOTest : public ::testing::Test {
protected:
  virtual void SetUp();
  virtual void TearDown();

protected:
  Common::CorrelationDAO dao;
  std::string testCorFilenameBase = "test";
  std::string testCorFilename = testCorFilenameBase + ".cor";
};
