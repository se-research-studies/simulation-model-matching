#pragma once

#include <gtest/gtest.h>

#include <FeatureSimulation/Common/DataManagement/FeatureSetDAO>

class FeatureSetDAOTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

protected:
    Common::FeatureSetDAO dao;
};

