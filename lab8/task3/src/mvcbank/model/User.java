package mvcbank.model;

public class User {
	private String username;
    private String password;
    private Money account_balance;
 
    public User(String username, String password, Money account_balance){
        this.username = username;
        this.password = password;
        this.account_balance = account_balance;
    }
 
    public String getUsername() {
        return username;
    }
 
    public void setUsername(String username) {
        this.username = username;
    }
 
    public String getPassword() {
        return password;
    }
 
    public void setPassword(String password) {
        this.password = password;
    }
    
	public Money getAccount_balance() {
		return account_balance;
	}

	public void setAccount_balance(Money account_balance) {
		this.account_balance = account_balance;
	}
	
    @Override
    public boolean equals(Object obj) {
    	if (!(obj instanceof User))
    		return false;
    	User obj_user = (User) obj;
    	
    	return username.equals(obj_user.username) && password.equals(obj_user.password);
    }
}
