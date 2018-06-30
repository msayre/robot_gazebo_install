# robot_gazebo_install

## Robot installation on VM

- Create a virtualbox (or similar) with ubuntu 16.04 64bit
- Under the VM manager set the network to bridged adaptor so it appears like its two different machines
- Clone and install dependencies
```
sudo apt -y install git
mkdir -p ~/catkin_ws/src && cd ~/catkin_ws/src
git clone https://github.com/msayre/robot_intercept
cd robot_gazebo_install && ./install.bash
```

## Running server on VM

```roslaunch server_services.launch```

## Running rviz on the operator console

- Do the same steps as above and run ```./install.bash```
- Then ```roslaunch client_services.launch```

## Configure IP addresses

```
sudo nano /etc/hosts/
```
- edit hosts to include operator IP
```
nano .bashrc
```
- edit .bashrc to include ROS_MASTER_URI=http://192.168.X.X:11311/ and ROS_IP=192.168.X.Y
