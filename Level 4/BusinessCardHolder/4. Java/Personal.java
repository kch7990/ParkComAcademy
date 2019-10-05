/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businesscardholder;

/**
 *
 * @author kch79
 */
public class Personal {
    private String name;
    private String telephoneNumber;
    private String emailAddress;
    private String position;
    
    public Personal(){
        this.name="";
        this.telephoneNumber="";
        this.emailAddress="";
        this.position="";
    }
    public Personal(String name, String telephoneNumber, String emailAddress, String position){
        this.name=name;
        this.telephoneNumber=telephoneNumber;
        this.emailAddress=emailAddress;
        this.position=position;
    }
    public boolean IsEqual(Personal other){
        boolean ret=false;
        if(this.name.compareTo(other.name)==0 &&
                this.telephoneNumber.compareTo(other.telephoneNumber)==0 &&
                this.emailAddress.compareTo(other.emailAddress)==0 &&
                this.position.compareTo(other.position)==0){
            ret=true;
        }
        return ret;
    }
    public boolean IsNotEqual(Personal other){
        boolean ret=false;
        if(this.name.compareTo(other.name)!=0 ||
                this.telephoneNumber.compareTo(other.telephoneNumber)!=0 ||
                this.emailAddress.compareTo(other.emailAddress)!=0 ||
                this.position.compareTo(other.position)!=0){
            ret=true;
        }
        return ret;
    }
    public String GetName(){
        return this.name;
    }
    public String GetTelephoneNumber(){
        return this.telephoneNumber;
    }
    public String GetEmailAddress(){
        return this.emailAddress;
    }
    public String GetPosition(){
        return this.position;
    }
}
