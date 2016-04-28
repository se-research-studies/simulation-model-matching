#include "featuresetdao_test.h"

#include <FeatureSimulation/Common/DataManagement/Database>

void FeatureSetDAOTest::SetUp() {
  Common::Database::getInstance().deleteRows(Common::FeatureSetsContract::TABLENAME, "");
}

void FeatureSetDAOTest::TearDown() {
  Common::Database::getInstance().deleteRows(Common::FeatureSetsContract::TABLENAME, "");
}

TEST_F(FeatureSetDAOTest, saveAndLoad) {
  Common::FeatureSet featureSet("recordingName");
  featureSet.addFrame(1, Common::Frame::fromString("{1,2,3};{4,5,6}"));
  featureSet.addFrame(2, Common::Frame::fromString("{7,8,9}"));
  dao.save(featureSet);

  Common::FeatureSet loadedFeatureSet = dao.load("recordingName");
  ASSERT_EQ("recordingName", loadedFeatureSet.getRecordingName());
  ASSERT_EQ(2, loadedFeatureSet.getFrameCount());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(1));
  ASSERT_EQ("{1,2,3};{4,5,6}", loadedFeatureSet.getFrame(1).toString());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(2));
  ASSERT_EQ("{7,8,9}", loadedFeatureSet.getFrame(2).toString());
}

TEST_F(FeatureSetDAOTest, load_ranged) {
  Common::FeatureSet featureSet("recordingName");
  featureSet.addFrame(1, Common::Frame::fromString("{1,2,3}"));
  featureSet.addFrame(2, Common::Frame::fromString("{4,5,6}"));
  featureSet.addFrame(3, Common::Frame::fromString("{7,8,9}"));
  featureSet.addFrame(4, Common::Frame::fromString("{10,11,12}"));
  featureSet.addFrame(5, Common::Frame::fromString("{13,14,15}"));
  dao.save(featureSet);

  Common::FeatureSet loadedFeatureSet = dao.load("recordingName", 2, 4);
  ASSERT_EQ(3, loadedFeatureSet.getFrameCount());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(2));
  ASSERT_EQ("{4,5,6}", loadedFeatureSet.getFrame(2).toString());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(3));
  ASSERT_EQ("{7,8,9}", loadedFeatureSet.getFrame(3).toString());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(4));
  ASSERT_EQ("{10,11,12}", loadedFeatureSet.getFrame(4).toString());
}
