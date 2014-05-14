package task1.model;

import java.util.ArrayList;
import java.util.List;

public class Host {
	
	public static List<Host> hosts = new ArrayList<Host>();
	
	private String name;
	private String ip;

	public Host(String name, String ip) {
		this.name = name;
		this.ip = ip;
	}

	public String getName(){ return(name); }

	public String getIp(){ return(ip); }

	public void setName(String name){ this.name = name; }

	public void setIp(String ip){ this.ip = ip; }
	
	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof Host))
			return false;
		
		Host host = (Host) obj;
		return host.ip.equals(ip) && host.ip.equals(ip);
	}

}