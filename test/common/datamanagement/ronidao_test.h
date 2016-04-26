#pragma once

#include <gtest/gtest.h>

#include <FeatureSimulationCommon/DataManagement/RoniDAO>

class RoniDAOTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;

protected:
  Common::RoniDAO dao;
  std::string testRoniFilenameBase = "test";
  std::string testRoniFilename = testRoniFilenameBase + ".roni";
};

