#include "featuresetdao_test.h"

#include <FeatureSimulation/Common/DataManagement/Database>

void FeatureSetDAOTest::SetUp() {
  dao.ensureTable();
  Common::Database::getInstance().deleteRows(Common::FeatureSetsContract::TABLENAME, "");
}

void FeatureSetDAOTest::TearDown() {
  Common::Database::getInstance().deleteRows(Common::FeatureSetsContract::TABLENAME, "");
}

TEST_F(FeatureSetDAOTest, saveAndLoad) {
  Common::FeatureSet featureSet("recordingName");
  featureSet.addFrame(1, Common::DirtyFrame::fromSqlString("{1,2,3};{4,5,6}"));
  featureSet.addFrame(2, Common::DirtyFrame::fromSqlString("{7,8,9}"));
  dao.save(featureSet);

  Common::FeatureSet loadedFeatureSet = dao.load("recordingName");
  ASSERT_EQ("recordingName", loadedFeatureSet.getRecordingName());
  ASSERT_EQ(2, loadedFeatureSet.getFrameCount());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(1));
  ASSERT_EQ("{1,2,3.000000};{4,5,6.000000}", loadedFeatureSet.getFrame(1).toSqlString());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(2));
  ASSERT_EQ("{7,8,9.000000}", loadedFeatureSet.getFrame(2).toSqlString());
}

TEST_F(FeatureSetDAOTest, load_ranged) {
  Common::FeatureSet featureSet("recordingName");
  featureSet.addFrame(1, Common::DirtyFrame::fromSqlString("{1,2,3}"));
  featureSet.addFrame(2, Common::DirtyFrame::fromSqlString("{4,5,6}"));
  featureSet.addFrame(3, Common::DirtyFrame::fromSqlString("{7,8,9}"));
  featureSet.addFrame(4, Common::DirtyFrame::fromSqlString("{10,11,12}"));
  featureSet.addFrame(5, Common::DirtyFrame::fromSqlString("{13,14,15}"));
  dao.save(featureSet);

  Common::FeatureSet loadedFeatureSet = dao.load("recordingName", 2, 4);
  ASSERT_EQ(3, loadedFeatureSet.getFrameCount());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(2));
  ASSERT_EQ("{4,5,6.000000}", loadedFeatureSet.getFrame(2).toSqlString());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(3));
  ASSERT_EQ("{7,8,9.000000}", loadedFeatureSet.getFrame(3).toSqlString());
  ASSERT_NO_THROW(loadedFeatureSet.getFrame(4));
  ASSERT_EQ("{10,11,12.000000}", loadedFeatureSet.getFrame(4).toSqlString());
}
