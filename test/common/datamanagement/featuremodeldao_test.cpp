#include "featuremodeldao_test.h"

#include <FeatureSimulationCommon/MakeUnique>
#include <FeatureSimulationCommon/DataManagement/Database>

void FeatureModelDAOTest::SetUp() {
  Common::Database::getInstance().deleteRows(Common::FeatureModelsContract::TABLENAME, "");
}

void FeatureModelDAOTest::TearDown() {
  Common::Database::getInstance().deleteRows(Common::FeatureModelsContract::TABLENAME, "");
}

TEST_F(FeatureModelDAOTest, saveAndLoad) {
  Common::Position startPosition({1, 2}, 3);
  Common::Position endPosition({4, 5}, 6);
  Common::Correlation correlation(1, 2, startPosition, endPosition);
  Common::FeatureSet featureSet("recordingName");
  Common::FeatureModel featureModel("simulationName", correlation, 0, std::move(featureSet));

  dao.save(featureModel);

  std::vector<Common::FeatureModel> loadedFeatureModels = dao.load("simulationName");
  ASSERT_EQ(1, loadedFeatureModels.size());
  ASSERT_EQ("simulationName", loadedFeatureModels.at(0).getSimulationName());
  ASSERT_EQ(0, loadedFeatureModels.at(0).getPermutation());
  ASSERT_EQ(1, loadedFeatureModels.at(0).getCorrelation().getStartFrame());
  ASSERT_EQ(2, loadedFeatureModels.at(0).getCorrelation().getEndFrame());
  ASSERT_EQ("{1,2,3}", loadedFeatureModels.at(0).getCorrelation().getStartPosition().toString());
  ASSERT_EQ("{4,5,6}", loadedFeatureModels.at(0).getCorrelation().getEndPosition().toString());
  ASSERT_EQ("recordingName", loadedFeatureModels.at(0).getFeatureSet().getRecordingName());
}

TEST_F(FeatureModelDAOTest, load_respects_correlation_frame_range) {
  Common::FeatureSetDAO featureSetDao;
  Common::FeatureSet featureSet("recordingName");
  featureSet.addFrame(1, Common::Frame::fromString("{1,2,3}"));
  featureSet.addFrame(2, Common::Frame::fromString("{4,5,6}"));
  featureSet.addFrame(3, Common::Frame::fromString("{7,8,9}"));
  featureSet.addFrame(4, Common::Frame::fromString("{10,11,12}"));
  featureSet.addFrame(5, Common::Frame::fromString("{13,14,15}"));
  featureSetDao.save(featureSet);

  Common::Position startPosition({1, 2}, 3);
  Common::Position endPosition({4, 5}, 6);
  Common::Correlation correlation(2, 4, startPosition, endPosition);
  Common::FeatureModel featureModel("simulationName", correlation, 0, std::move(featureSet));
  dao.save(featureModel);

  std::vector<Common::FeatureModel> loadedFeatureModels = dao.load("simulationName");
  ASSERT_EQ(3, loadedFeatureModels.at(0).getFeatureSet().getFrameCount());
  ASSERT_NO_THROW(loadedFeatureModels.at(0).getFeatureSet().getFrame(2));
  ASSERT_EQ("{4,5,6}", loadedFeatureModels.at(0).getFeatureSet().getFrame(2).toString());
  ASSERT_NO_THROW(loadedFeatureModels.at(0).getFeatureSet().getFrame(3));
  ASSERT_EQ("{7,8,9}", loadedFeatureModels.at(0).getFeatureSet().getFrame(3).toString());
  ASSERT_NO_THROW(loadedFeatureModels.at(0).getFeatureSet().getFrame(4));
  ASSERT_EQ("{10,11,12}", loadedFeatureModels.at(0).getFeatureSet().getFrame(4).toString());
}

TEST_F(FeatureModelDAOTest, load_loads_all_permutations) {
  Common::Position startPosition({1, 2}, 3);
  Common::Position endPosition({4, 5}, 6);
  Common::Correlation correlation(1, 2, startPosition, endPosition);
  Common::FeatureSet featureSet("recordingName");
  Common::FeatureModel featureModel1("simulationName", correlation, 0, std::move(featureSet));

  Common::Correlation correlation2(3, 4, startPosition, endPosition);
  Common::FeatureSet featureSet2("recordingName");
  Common::FeatureModel featureModel2("simulationName", correlation2, 1, std::move(featureSet2));

  dao.save(featureModel1);
  dao.save(featureModel2);

  std::vector<Common::FeatureModel> loadedFeatureModels = dao.load("simulationName");
  ASSERT_EQ(2, loadedFeatureModels.size());
  ASSERT_EQ(0, loadedFeatureModels.at(0).getPermutation());
  ASSERT_EQ(1, loadedFeatureModels.at(1).getPermutation());
}
