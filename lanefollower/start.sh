#!/bin/bash
echo "=== Starting Infrastructure ==="
# In directory of configuration file, scenario and car objx:
x-terminal-emulator -t "odsupercomponent" -e "bash -c \"odsupercomponent --cid=111 exec bash\""
x-terminal-emulator -t "odsimvehicle" -e "bash -c \"odsimvehicle --cid=111 --freq=10; exec bash\""
x-terminal-emulator -t "odsimirus" -e "bash -c \"odsimirus --cid=111 --freq=10; exec bash\""
x-terminal-emulator -t "odcockpit" -e "bash -c \"odcockpit --cid=111; exec bash\""
x-terminal-emulator -t "odsimcamera" -e "bash -c \"odsimcamera --cid=111 --freq=10; exec bash\""
# Wait
sleep 5
# In lanefollower directory:
echo "=== Starting Lanefollower ==="
cd ./build/
x-terminal-emulator -t "lanefollower" -e "bash -c \"./lanefollower --cid=111 --freq=10; exec bash\""
