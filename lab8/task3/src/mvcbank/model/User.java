package mvcbank.model;

public class User {
	private Integer id;
	private String username;
    private String password;
    private Money account_balance;
 
    public User(Integer id, String username, String password, Money account_balance){
    	this.id = id;
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
	
	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}
	
    @Override
    public boolean equals(Object obj) {
    	if (!(obj instanceof User))
    		return false;
    	
    	User obj_user = (User) obj;
    	
    	// look by id if it's set
    	if(id != null && obj_user.id != null)
    		return id == obj_user.id;
    	
    	return username.equals(obj_user.username) && password.equals(obj_user.password);
    }
}
