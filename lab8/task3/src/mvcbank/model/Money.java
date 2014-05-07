package mvcbank.model;

public class Money {
	private Double balance;
	private String currency;
	
	public Money(Double balance, String currency) {
		this.balance = balance;
		this.currency = currency;
	}
	
	public Double getBalance() {
		return balance;
	}
	public void setBalance(Double balance) {
		this.balance = balance;
	}
	public String getCurrency() {
		return currency;
	}
	public void setCurrency(String currency) {
		this.currency = currency;
	}
	
	@Override
	public String toString() {
		return String.format("%.2f %s", balance, currency);
	}
}
