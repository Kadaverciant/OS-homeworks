#!/bin/bash

#create lofs.img with size 56MB
dd if=/dev/zero of=lofs.img bs=1M count=56
#create the loop device
sudo losetup -fP lofs.img
#create the filesystem
sudo mkfs.ext4 lofs.img
#create directory
mkdir lofsdisk
#mount the created filesystem
sudo mount -o loop lofs.img lofsdisk

#usefull commands:
#df -hP lofsdisk
#sudo umount lofsdisk
