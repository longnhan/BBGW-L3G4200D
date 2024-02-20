**Embedded Linux Project with BeagleBone Green Wireless**

**Introduction**

This project is an embedded Linux application tailored for the BeagleBone Green Wireless platform. It facilitates seamless communication with an L3G4200 gyroscope sensor via the I2C interface. Developed entirely from scratch, this project provides a robust foundation for interfacing with sensors and collecting data in embedded systems.

**Setup**

To set up the project, follow these steps:

Connect the L3G4200 gyroscope sensor to pins 19 and 20 on the BeagleBone Green Wireless board.
Ensure that the necessary I2C drivers are enabled on the BeagleBone Green Wireless board.
Clone the project repository to your development environment.

**Usage**

1) Build for Release:

Run /tool/build.sh to build the project for release. This script compiles the source code and generates the release executable file.

2) Build for Debugging:

Use /tool/debug.sh to build the project for debugging purposes. This script compiles the source code with debugging symbols enabled, facilitating debugging sessions.

3) Transfer to BeagleBone Green Wireless (BBGW):

After building, copy the generated executable or files located in the build/ directory to the BeagleBone Green Wireless board.
Use /tool/scp_bbgw.sh to securely copy the built files to the BBGW.
Run the Application:

Once the files are transferred, execute the application on the BeagleBone Green Wireless board according to your requirements.

**Additional Information**

For any additional information or troubleshooting, refer to the project documentation.
If you encounter any issues or have questions, feel free to reach out to the project maintainers.

**License**

This project is licensed under the MIT License.

Feel free to adjust the contents as needed and include any specific details relevant to your project.