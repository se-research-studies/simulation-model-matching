#pragma once

#include <gtest/gtest.h>

#include <FeatureSimulationCommon/DataManagement/RoniDAO>

class RoniDAOTest : public ::testing::Test {
protected:
  virtual void SetUp();
  virtual void TearDown();

protected:
  Common::RoniDAO dao;
  std::string testRoniFilenameBase = "test";
  std::string testRoniFilename = testRoniFilenameBase + ".roni";
};

