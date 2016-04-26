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
  std::unique_ptr<Common::FeatureSet> featureSet = std::make_unique<Common::FeatureSet>("recordingName");
  Common::FeatureModel featureModel("simulationName", correlation, 0, move(featureSet));

  dao.save(featureModel);

  std::vector<std::unique_ptr<Common::FeatureModel>> loadedFeatureModels = dao.load("simulationName");
  ASSERT_EQ(1, loadedFeatureModels.size());
  Common::FeatureModel* loadedFeatureModel = loadedFeatureModels.at(0).get();
  ASSERT_EQ("simulationName", loadedFeatureModel->simulationName);
  ASSERT_EQ(0, loadedFeatureModel->permutation);
  ASSERT_EQ(1, loadedFeatureModel->correlation.startFrame);
  ASSERT_EQ(2, loadedFeatureModel->correlation.endFrame);
  ASSERT_EQ("{1,2,3}", loadedFeatureModel->correlation.startPosition.toString());
  ASSERT_EQ("{4,5,6}", loadedFeatureModel->correlation.endPosition.toString());
  ASSERT_NE(nullptr, loadedFeatureModel->featureSet);
  ASSERT_EQ("recordingName", loadedFeatureModel->featureSet->getRecordingName());
}

TEST_F(FeatureModelDAOTest, load_respects_correlation_frame_range) {
  Common::FeatureSetDAO featureSetDao;
  std::unique_ptr<Common::FeatureSet> featureSet = std::make_unique<Common::FeatureSet>("recordingName");
  featureSet->addFrame(1, Common::Frame::fromString("{1,2,3}"));
  featureSet->addFrame(2, Common::Frame::fromString("{4,5,6}"));
  featureSet->addFrame(3, Common::Frame::fromString("{7,8,9}"));
  featureSet->addFrame(4, Common::Frame::fromString("{10,11,12}"));
  featureSet->addFrame(5, Common::Frame::fromString("{13,14,15}"));
  featureSetDao.save(*featureSet);

  Common::Position startPosition({1, 2}, 3);
  Common::Position endPosition({4, 5}, 6);
  Common::Correlation correlation(2, 4, startPosition, endPosition);
  Common::FeatureModel featureModel("simulationName", correlation, 0, move(featureSet));
  dao.save(featureModel);

  std::vector<std::unique_ptr<Common::FeatureModel>> loadedFeatureModels = dao.load("simulationName");
  Common::FeatureModel* loadedFeatureModel = loadedFeatureModels.at(0).get();
  ASSERT_EQ(3, loadedFeatureModel->featureSet->getFrameCount());
  ASSERT_NE(nullptr, loadedFeatureModel->featureSet->getFrame(2));
  ASSERT_EQ("{4,5,6}", loadedFeatureModel->featureSet->getFrame(2)->toString());
  ASSERT_NE(nullptr, loadedFeatureModel->featureSet->getFrame(3));
  ASSERT_EQ("{7,8,9}", loadedFeatureModel->featureSet->getFrame(3)->toString());
  ASSERT_NE(nullptr, loadedFeatureModel->featureSet->getFrame(4));
  ASSERT_EQ("{10,11,12}", loadedFeatureModel->featureSet->getFrame(4)->toString());
}

TEST_F(FeatureModelDAOTest, load_loads_all_permutations) {
  Common::Position startPosition({1, 2}, 3);
  Common::Position endPosition({4, 5}, 6);
  Common::Correlation correlation(1, 2, startPosition, endPosition);
  std::unique_ptr<Common::FeatureSet> featureSet = std::make_unique<Common::FeatureSet>("recordingName");
  Common::FeatureModel featureModel1("simulationName", correlation, 0, move(featureSet));

  Common::Correlation correlation2(3, 4, startPosition, endPosition);
  std::unique_ptr<Common::FeatureSet> featureSet2 = std::make_unique<Common::FeatureSet>("recordingName");
  Common::FeatureModel featureModel2("simulationName", correlation2, 1, move(featureSet2));

  dao.save(featureModel1);
  dao.save(featureModel2);

  std::vector<std::unique_ptr<Common::FeatureModel>> loadedFeatureModels = dao.load("simulationName");
  ASSERT_EQ(2, loadedFeatureModels.size());
  ASSERT_EQ(0, loadedFeatureModels.at(0)->permutation);
  ASSERT_EQ(1, loadedFeatureModels.at(1)->permutation);
}
