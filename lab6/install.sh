1) install hadoop1 and hadoop2
	vagrant up
	vagrant ssh hadoop1 # access hadoop1
	vagrant ssh hadoop1 # access hadoop2

2) execute following commands on virtual machines
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
	curl -O http://archive.cloudera.com/cm4/installer/latest/cloudera-manager-installer.bin
	chmod +x cloudera-manager-installer.bin
	sudo ./cloudera-manager-installer.bin

	# open 192.168.0.101:7180

3) instalation

	login as admin/admin

	search for following vms
		hadoop1
		hadoop2

	connect via ssh
		root/vagrant

4) www
http://192.168.0.101:7180/
http://192.168.0.101:50030/