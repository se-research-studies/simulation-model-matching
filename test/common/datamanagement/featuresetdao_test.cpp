#include "featuresetdao_test.h"

#include <FeatureSimulationCommon/MakeUnique>
#include <FeatureSimulationCommon/DataManagement/Database>
#include <FeatureSimulationCommon/DataManagement/FeatureSetDAO>

TEST(FeatureSetDAOTest, saveAndRead) {
  Common::FeatureSetDAO dao;
  Common::Database::getInstance().deleteRows(Common::FeatureSetsContract::TABLENAME, "");

  Common::FeatureSet featureSet("recordingName");
  featureSet.addFrame(1, Common::Frame::fromString("{1,2,3};{4,5,6}"));
  featureSet.addFrame(2, Common::Frame::fromString("{7,8,9}"));
  dao.save(featureSet);

  std::unique_ptr<Common::FeatureSet> loadedFeatureSet = dao.load("recordingName");
  ASSERT_EQ("recordingName", loadedFeatureSet->getRecordingName());
  ASSERT_EQ(2, loadedFeatureSet->getFrameCount());
  ASSERT_NE(nullptr, loadedFeatureSet->getFrame(1));
  ASSERT_EQ("{1,2,3};{4,5,6}", loadedFeatureSet->getFrame(1)->toString());
  ASSERT_NE(nullptr, loadedFeatureSet->getFrame(2));
  ASSERT_EQ("{7,8,9}", loadedFeatureSet->getFrame(2)->toString());
}

TEST(FeatureSetDAOTest, load_ranged) {
  ASSERT_TRUE(false);
}
