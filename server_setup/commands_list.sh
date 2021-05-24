echo "Hello, googlers!"


#        IP ADDRESS INFORMATION:
# get the proper address for web server:
# nmcli -p device show

# to get local ip address
# ip address

# to list public ip address:
# sudo curl -s https://icanhazip.com 



# RAM DISK setup:
sudo mkdir -p /mnt/ramdisk
sudo mount -t tmpfs -o rw,size=3G tmpfs /mnt/ramdisk


# copy files to the ram disk as it is volatile
sudo cp -r /home/crawler/test-websites /mnt/ramdisk


# start nginx server. Note that nginx configuration is already done accoring to Daria's tutorial
sudo systemctl start nginx

# update the configuration
sudo systemctl restart nginx

echo "Setup is done. Now we are able to accept requests"

