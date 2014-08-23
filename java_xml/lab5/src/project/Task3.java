package project;

import java.io.File;
import java.io.FileInputStream;
import java.util.HashSet;
import java.util.Set;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamReader;

class Contact {
	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSurname() {
		return surname;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public String getHomeAddress() {
		return homeAddress;
	}

	public void setHomeAddress(String homeAddress) {
		this.homeAddress = homeAddress;
	}

	public String getPhone() {
		return phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public String getMobile() {
		return mobile;
	}

	public void setMobile(String mobile) {
		this.mobile = mobile;
	}

	public String getJob() {
		return job;
	}

	public void setJob(String job) {
		this.job = job;
	}

	String id;
	String name;
	String surname;
	String homeAddress;
	String phone;
	String mobile;
	String job;
	
	@Override
	public String toString() {
		return "Contact [id=" + id + ", name=" + name + ", surname=" + surname
				+ ", homeAddress=" + homeAddress + ", phone=" + phone
				+ ", mobile=" + mobile + ", job=" + job + "]";
	}
}

public class Task3 {

	public static void main(String[] args) {
		HashSet<Contact> contactList = new HashSet<>();
		Contact contact = null;
		String tagContent = null;
		XMLInputFactory factory = XMLInputFactory.newInstance();
		XMLStreamReader reader;
		try {
			reader = factory
					.createXMLStreamReader(new FileInputStream(new File(
							"lab1_task1.xml")));

			while (reader.hasNext()) {
				int event = reader.next();
	
				switch (event) {
				case XMLStreamConstants.START_ELEMENT:
					switch (reader.getLocalName()) {
					case "contact":
						contact = new Contact();
						contact.setId(reader.getAttributeValue(0));
						break;
					}
					break;
	
				case XMLStreamConstants.CHARACTERS:
					tagContent = reader.getText().trim();
					break;
	
				case XMLStreamConstants.END_ELEMENT:
					switch (reader.getLocalName()) {
					case "contact":
						contactList.add(contact);
						break;
					case "name":
						contact.setName(tagContent);
						break;
					case "surname":
						contact.setSurname(tagContent);
						break;
					case "home_address":
						contact.setHomeAddress(tagContent);
						break;
					case "phone":
						contact.setPhone(tagContent);
						break;
					case "mobile":
						contact.setMobile(tagContent);
						break;
					case "job":
						contact.setJob(tagContent);
						break;
					}
					break;

				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} 

		for (Contact con : contactList) {
			System.out.println(con);
		}
	}
}
