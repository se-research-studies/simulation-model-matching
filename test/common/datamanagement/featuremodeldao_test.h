#pragma once

#include <gtest/gtest.h>

#include <FeatureSimulation/Common/DataManagement/FeatureModelDAO>

class FeatureModelDAOTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;

protected:
  Common::FeatureModelDAO dao;
};
