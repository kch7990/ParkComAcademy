/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package addressbook;

/**
 *
 * @author kch79
 */
public class Personal {
    private String name;
    private String address;
    private String telephoneNumber;
    private String emailAddress;
    
    public Personal(){
        this.name="";
        this.address="";
        this.telephoneNumber="";
        this.emailAddress="";
    }
    public Personal(String name, String address, String telephoneNumber, String emailAddress){
        this.name=name;
        this.address=address;
        this.telephoneNumber=telephoneNumber;
        this.emailAddress=emailAddress;
    }
    public boolean IsEqual(Personal other){
        boolean ret=false;
        if(this.name.compareTo(other.name)==0 &&
           this.address.compareTo(other.address)==0 &&
           this.telephoneNumber.compareTo(other.telephoneNumber)==0 &&
           this.emailAddress.compareTo(other.emailAddress)==0) {
            ret=true;
        }
        return ret;
    }
    public boolean IsNotEqual(Personal other){
        boolean ret=false;
        if(this.name.compareTo(other.name)!=0 ||
           this.address.compareTo(other.address)!=0 ||
           this.telephoneNumber.compareTo(other.telephoneNumber)!=0 ||
           this.emailAddress.compareTo(other.emailAddress)!=0){
            ret=true;
        }
        return ret;
    }
    public String GetName(){
        return this.name;
    }
    public String GetAddress(){
        return this.address;
    }
    public String GetTelephoneNumber(){
        return this.telephoneNumber;
    }
    public String GetEmailAddress(){
        return this.emailAddress;
    }
}
