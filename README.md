# Arduino Sensor Controller
Configs and setup instructions for our Arduino Sensor Controller

## 1 Pre-Requistites
- Arduino UNO
- Serial Cable
- Components for Sensors

## 2 Deployment
Check if the ./deploy_sketch.sh executable
``` bash
chmod +x deploy_sketch.sh
```

Run the script to deploy the controller_main.ino which contains all the sensor collection and control code. DO THIS BEFORE RUNNING PYTHON SCRIPTS ON RPBI-CORE
``` bash
./deploy_sketch.sh
```