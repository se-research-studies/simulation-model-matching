#include "ronidao_test.h"

#include <fstream>

void RoniDAOTest::SetUp() {
  std::ofstream file;
  file.open(testRoniFilename);
  if (!file.is_open()) {
    FAIL() << "Could not create " + testRoniFilename;
  }
  std::string contents = R"({
 "regions": [
   {
     "topLeft": {
       "x": 1,
       "y": 2
     },
     "topRight": {
       "x": 3,
       "y": 4
     },
     "bottomLeft": {
       "x": 5,
       "y": 6
     },
     "bottomRight": {
       "x": 7,
       "y": 8
     }
   },
   {
     "topLeft": {
       "x": 9,
       "y": 10
     },
     "topRight": {
       "x": 11,
       "y": 12
     },
     "bottomLeft": {
       "x": 13,
       "y": 14
     },
     "bottomRight": {
       "x": 15,
       "y": 16
     }
   }
 ]
})";
  file << contents;
  file.close();
  if (file.fail()) {
    FAIL() << "Could not save " + testRoniFilename;
  }
}

void RoniDAOTest::TearDown() {
  if (std::remove(testRoniFilename.c_str()) != 0) {
    FAIL() << "Could not remove " + testRoniFilename;
  }
}

TEST_F(RoniDAOTest, load_GIVEN_invalid_filename_THEN_throws_exception) {
  ASSERT_THROW(dao.load("nonexistant.invalid"), std::runtime_error);
}

TEST_F(RoniDAOTest, load_GIVEN_valid_file_THEN_converts_content) {
  std::vector<Common::Region> result = dao.load(testRoniFilename);

  ASSERT_EQ(2, result.size());

  Common::Region firstRegion = result.at(0);
  ASSERT_EQ(1, firstRegion.topLeft.x);
  ASSERT_EQ(2, firstRegion.topLeft.y);
  ASSERT_EQ(3, firstRegion.topRight.x);
  ASSERT_EQ(4, firstRegion.topRight.y);
  ASSERT_EQ(5, firstRegion.bottomLeft.x);
  ASSERT_EQ(6, firstRegion.bottomLeft.y);
  ASSERT_EQ(7, firstRegion.bottomRight.x);
  ASSERT_EQ(8, firstRegion.bottomRight.y);

  Common::Region secondRegion = result.at(1);
  ASSERT_EQ(9, secondRegion.topLeft.x);
  ASSERT_EQ(10, secondRegion.topLeft.y);
  ASSERT_EQ(11, secondRegion.topRight.x);
  ASSERT_EQ(12, secondRegion.topRight.y);
  ASSERT_EQ(13, secondRegion.bottomLeft.x);
  ASSERT_EQ(14, secondRegion.bottomLeft.y);
  ASSERT_EQ(15, secondRegion.bottomRight.x);
  ASSERT_EQ(16, secondRegion.bottomRight.y);
}

TEST_F(RoniDAOTest, load_GIVEN_recording_filename_THEN_uses_same_base_name) {
  std::vector<Common::Region> result;

  ASSERT_NO_THROW(result = dao.load(testRoniFilenameBase + ".rec"));

  ASSERT_EQ(2, result.size());
}
