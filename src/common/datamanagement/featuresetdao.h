#pragma once

#include <FeatureSimulation/Common/DataManagement/dataaccessobject.h>
#include <FeatureSimulation/Common/Data/featureset.h>
#include <FeatureSimulation/Common/DataManagement/cursor.h>
#include <FeatureSimulation/Common/DataManagement/tablefield.h>

namespace Common {

    namespace FeatureSetsContract {
        static const std::string TABLENAME = "FeatureSets";
        static const std::string COL_RECORDINGNAME = "recordingName";
        static const std::string COL_ID = "id";
        static const std::string COL_FRAME = "frame";
        static const std::string COL_FEATURES = "features";
        static const uint8_t INDEX_RECORDINGNAME = 0;
        static const uint8_t INDEX_ID = 1;
        static const uint8_t INDEX_FRAME = 2;
        static const uint8_t INDEX_FEATURES = 3;
    }

    class FeatureSetDAO : public DataAccessObject {
    public:
        void ensureTable() const;
        std::unique_ptr<FeatureSet> load(const std::string& recordingName) const;
        std::unique_ptr<FeatureSet> load(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
        void save(const FeatureSet& featureSet) const;
        void deleteAll(const std::string& recordingName, const std::string& id) const;

    private:
        std::string selectionString(const std::string& recordingName) const;
        std::string selectionString(const std::string& recordingName, uint32_t startFrame, uint32_t endFrame) const;
        std::unique_ptr<FeatureSet> toFeatureSet(const std::string& recordingName, Cursor& cursor) const;
        std::vector<TableField> toRow(const std::string& recordingName, const std::string& id, const std::pair<const uint32_t, DirtyFrame>& frame) const;
    };

} // namespace FeatureExtraction

