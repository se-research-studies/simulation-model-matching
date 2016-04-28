#include "correlationdao_test.h"

#include <fstream>

void CorrelationDAOTest::SetUp() {
  std::ofstream file;
  file.open(testCorFilename);
  if (!file.is_open()) {
    FAIL() << "Could not create " + testCorFilename;
  }
  std::string contents = R"({
  "correlations": [
   {
     "recordingFile": "recFile1.rec",
     "startFrame": 4,
     "endFrame": 15,
     "startPosition": {
       "x": 123,
       "y": 456,
       "theta": 78
     },
     "endPosition": {
       "x": 901,
       "y": 234,
       "theta": 56
     }
   },
   {
     "recordingFile": "recFile2.rec",
     "startFrame": 1,
     "endFrame": 12,
     "startPosition": {
       "x": 876,
       "y": 543,
       "theta": 21
     },
     "endPosition": {
       "x": 111,
       "y": 222,
       "theta": 333
     }
   }
  ]
})";
  file << contents;
  file.close();
  if (file.fail()) {
    FAIL() << "Could not save " + testCorFilename;
  }
}

void CorrelationDAOTest::TearDown() {
  if (std::remove(testCorFilename.c_str()) != 0) {
    FAIL() << "Could not remove " + testCorFilename;
  }
}

TEST_F(CorrelationDAOTest, load_GIVEN_invalid_filename_THEN_throws_exception) {
  ASSERT_THROW(dao.load("nonexistant.invalid"), std::runtime_error);
}

TEST_F(CorrelationDAOTest, load_GIVEN_valid_file_THEN_converts_content) {
  std::unordered_map<std::string, Common::Correlation> result = dao.load(testCorFilename);

  ASSERT_EQ(2, result.size());
  ASSERT_EQ(1, result.count("recFile1.rec"));
  ASSERT_EQ(1, result.count("recFile2.rec"));

  Common::Correlation firstCorrelation = result.at("recFile1.rec");
  ASSERT_EQ(4, firstCorrelation.getStartFrame());
  ASSERT_EQ(15, firstCorrelation.getEndFrame());
  ASSERT_EQ(123, firstCorrelation.getStartPosition().getX());
  ASSERT_EQ(456, firstCorrelation.getStartPosition().getY());
  ASSERT_EQ(78, firstCorrelation.getStartPosition().getTheta());
  ASSERT_EQ(901, firstCorrelation.getEndPosition().getX());
  ASSERT_EQ(234, firstCorrelation.getEndPosition().getY());
  ASSERT_EQ(56, firstCorrelation.getEndPosition().getTheta());

  Common::Correlation secondCorrelation = result.at("recFile2.rec");
  ASSERT_EQ(1, secondCorrelation.getStartFrame());
  ASSERT_EQ(12, secondCorrelation.getEndFrame());
  ASSERT_EQ(876, secondCorrelation.getStartPosition().getX());
  ASSERT_EQ(543, secondCorrelation.getStartPosition().getY());
  ASSERT_EQ(21, secondCorrelation.getStartPosition().getTheta());
  ASSERT_EQ(111, secondCorrelation.getEndPosition().getX());
  ASSERT_EQ(222, secondCorrelation.getEndPosition().getY());
  ASSERT_EQ(333, secondCorrelation.getEndPosition().getTheta());
}

TEST_F(CorrelationDAOTest, load_GIVEN_simulation_filename_THEN_uses_same_base_name) {
  std::unordered_map<std::string, Common::Correlation> result;

  ASSERT_NO_THROW(result = dao.load(testCorFilenameBase + ".xyz"));

  ASSERT_EQ(2, result.size());
  ASSERT_EQ(1, result.count("recFile1.rec"));
  ASSERT_EQ(1, result.count("recFile2.rec"));
}
