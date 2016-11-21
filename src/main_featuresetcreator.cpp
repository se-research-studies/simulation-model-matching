#include <iostream>

#include <FeatureSimulation/Common/DataManagement/database.h>

#include <FeatureSimulation/FeatureSetCreation/featuresetcreator.h>
#include <FeatureSimulation/FeatureSetCreation/guicontroler.h>
#include <FeatureSimulation/FeatureSetCreation/settings.h>
#include <FeatureSimulation/FeatureSetCreation/settingsreader.h>
#include <FeatureSimulation/FeatureSetCreation/settingsvalidator.h>

int main(int argc, char *argv[]) {
    try {
        FeatureSetCreation::Settings settings = FeatureSetCreation::FeatureSettingsReader::readSettings(argc, argv);
        FeatureSetCreation::GuiController::getInstance().setEnabled(settings.guiEnabled);
        Common::Database::getInstance().setDbFilename(argv[0], settings.database);

        FeatureSetCreation::SettingsValidator validator;
        validator.validate(settings);

        FeatureSetCreation::FeatureSetCreator featureSetCreator(settings);
        featureSetCreator.createFeatureSet();

        exit(EXIT_SUCCESS);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
