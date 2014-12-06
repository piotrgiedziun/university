import nmap
from prettytable import PrettyTable


# scan network - dispaly all opened ports in given range
nm = nmap.PortScanner()
nm.scan('156.17.40.1-255', '22-443')


tab = PrettyTable(["IP address", "Protocol", "Port", "Product name",
                   "Version", "Extra info"])

for host in nm.all_hosts():
    for proto in nm[host].all_protocols():
        lport = nm[host][proto].keys()
        lport.sort()
        for port in lport:
            # incompatible with installed nmap version
            if not isinstance(port, int):
                continue
            item = nm[host][proto][port]
            # skip closed
            if not item['state'] == "open":
                continue

            tab.add_row([host, proto, port, item['product'], item['version'],
                        item['extrainfo']])

print tab
