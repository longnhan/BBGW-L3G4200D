**Embedded Linux Project with BeagleBone Green Wireless**

**Introduction**

This project is an embedded Linux application tailored for the BeagleBone Green Wireless platform. 

It facilitates seamless communication with an L3G4200 gyroscope sensor via the I2C interface and POSIX IPC such as semaphore, message queue, multithread,.. 

Developed entirely from scratch, this project provides a robust foundation for interfacing with sensors and collecting data in embedded systems.

**Setup**

To set up the project, follow these steps:

Connect the L3G4200 gyroscope sensor as shown in diagram.png

Ensure that the necessary I2C drivers are enabled on the BeagleBone Green Wireless board.

Clone the project repository to your development environment, refer the flow.png for SW's understanding

**Usage**

1) Compile the project:

Use /tool/build.sh to compile for either release(1) or debug(2) purpose.

2) Transfer to BeagleBone Green Wireless (BBGW):

From the BBGW directory, create a directory named /home/debian/l3g4_prj/ to store the build/

After building, copy the generated executable or files located in the build/ directory to the BeagleBone Green Wireless board.
Use /tool/scp_bbgw.sh to securely copy the built files to the BBGW.
Run the Application:

Once the files are transferred, execute the application on the BeagleBone Green Wireless board according to your requirements.

**Additional Information**

For any additional information or troubleshooting, refer to the project documentation.

If you encounter any issues or have questions, feel free to reach out to the project maintainers.

Compilation will create 2 executed files (l3g4_prj_main and l3g4_prj_logfile). Lets run the l3g4_prj_main, the l3g4_prj_logfile will be call by the main.

**Setup daemon for auto start from power up**
touch  /etc/systemd/system/autostart.service

    [Unit]
    Description=My Auto start Program

    [Service]
    ExecStart=/home/debian/l3g4_prj/build/l3g4_prj_main
    Restart=always
    User=debian
    StandardOutput=journal
    StandardError=journal

    [Install]
    WantedBy=multi-user.target

Then run:

    sudo  systemctl daemon-reload
    sudo  systemctl enable nhan_autostart.service
    sudo  systemctl start nhan_autostart.service


**License**

This project is licensed under the MIT License.

Feel free to adjust the contents as needed and include any specific details relevant to your project.
