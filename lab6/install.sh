# set up hosts file (192.168.0.101 and 192.168.0.102)
sudo vi /etc/hosts
# add 
192.168.0.101	hadoop1
192.168.0.102	hadoop2

# disable firewall on both 192.168.0.101 and 192.168.0.102
sudo /etc/init.d/iptables save
sudo /etc/init.d/iptables stop
sudo /etc/init.d/ip6tables save
sudo /etc/init.d/ip6tables stop
sudo chkconfig
sudo service network reload

# install cloudera only 192.168.0.101
url -O http://archive.cloudera.com/cm4/installer/latest/cloudera-manager-installer.bin
chmod +x cloudera-manager-installer.bin
sudo ./cloudera-manager-installer.bin

# open 192.168.0.101:7180