#include "abstractparticipant.h"

#include <opendavinci/generated/odcore/data/image/SharedImage.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/odcore/base/Lock.h>

namespace SimulationGame {

    AbstractParticipant::AbstractParticipant(int argc, char** argv, const std::string& name)
        : odcore::base::module::TimeTriggeredConferenceClientModule(argc, argv, name)
    {
    }

    AbstractParticipant::~AbstractParticipant()
    {
    }

    void AbstractParticipant::setUp()
    {
        //        // Initialize fonts.
        //        const double hscale = 0.4;
        //        const double vscale = 0.3;
        //        const double shear = 0.2;
        //        const int thickness = 1;
        //        const int lineType = 6;

        //        cvInitFont(&m_font, CV_FONT_HERSHEY_DUPLEX, hscale, vscale, shear, thickness, lineType);

        //        // Get configuration data.
        //        KeyValueConfiguration kv = getKeyValueConfiguration();
        //        m_debug = kv.getValue<int32_t> ("lanefollower.debug") == 1;
    }

    void AbstractParticipant::tearDown()
    {

    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode AbstractParticipant::body()
    {
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            odcore::data::Container container = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
            if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
                odcore::data::image::SharedImage sharedImage = container.getData<odcore::data::image::SharedImage>();
                std::shared_ptr<odcore::wrapper::SharedMemory> sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(sharedImage.getName());
                if (sharedImageMemory->isValid()) {
                    odcore::base::Lock l(sharedImageMemory);
                    cv::Mat image(sharedImage.getWidth(), sharedImage.getHeight(), CV_MAKETYPE(CV_8U, sharedImage.getBytesPerPixel()), sharedImageMemory->getSharedMemory());
                    processImage(image);
                }
            }
//            Container c2(m_vehicleControl);
//            // Send container.
//            getConference().send(c2);

        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // namespace SimulationGame
