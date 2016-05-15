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
    ASSERT_EQ(1, firstRegion.getTopLeft().getX());
    ASSERT_EQ(2, firstRegion.getTopLeft().getY());
    ASSERT_EQ(3, firstRegion.getTopRight().getX());
    ASSERT_EQ(4, firstRegion.getTopRight().getY());
    ASSERT_EQ(5, firstRegion.getBottomLeft().getX());
    ASSERT_EQ(6, firstRegion.getBottomLeft().getY());
    ASSERT_EQ(7, firstRegion.getBottomRight().getX());
    ASSERT_EQ(8, firstRegion.getBottomRight().getY());

    Common::Region secondRegion = result.at(1);
    ASSERT_EQ(9, secondRegion.getTopLeft().getX());
    ASSERT_EQ(10, secondRegion.getTopLeft().getY());
    ASSERT_EQ(11, secondRegion.getTopRight().getX());
    ASSERT_EQ(12, secondRegion.getTopRight().getY());
    ASSERT_EQ(13, secondRegion.getBottomLeft().getX());
    ASSERT_EQ(14, secondRegion.getBottomLeft().getY());
    ASSERT_EQ(15, secondRegion.getBottomRight().getX());
    ASSERT_EQ(16, secondRegion.getBottomRight().getY());
}

TEST_F(RoniDAOTest, load_GIVEN_recording_filename_THEN_uses_same_base_name) {
    std::vector<Common::Region> result;

    ASSERT_NO_THROW(result = dao.load(testRoniFilenameBase + ".rec"));

    ASSERT_EQ(2, result.size());
}
