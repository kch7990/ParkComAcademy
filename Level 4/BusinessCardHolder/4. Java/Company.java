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
public class Company {
    private String name;
    private String address;
    private String telephoneNumber;
    private String faxNumber;
    private String url;
    
    public Company(){
        this.name="";
        this.address="";
        this.telephoneNumber="";
        this.faxNumber="";
        this.url="";
    }
    public Company(String name, String address, String telephoneNumber, String faxNumber, String url){
        this.name=name;
        this.address=address;
        this.telephoneNumber=telephoneNumber;
        this.faxNumber=faxNumber;
        this.url=url;
    }
    public boolean IsEqual(Company other){
        boolean ret=false;
        if(this.name.compareTo(other.name)==0 &&
           this.address.compareTo(other.address)==0 &&
           this.telephoneNumber.compareTo(other.telephoneNumber)==0 &&
           this.faxNumber.compareTo(other.faxNumber)==0 &&
           this.url.compareTo(other.url)==0){
            ret=true;
        }
        return ret;
    }
    public boolean IsNotEqual(Company other){
        boolean ret=false;
        if(this.name.compareTo(other.name)!=0 ||
                this.address.compareTo(other.address)!=0 ||
                this.telephoneNumber.compareTo(other.telephoneNumber)!=0 ||
                this.faxNumber.compareTo(other.faxNumber)!=0 ||
                this.url.compareTo(other.url)!=0){
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
    public String GetFaxNumber(){
        return this.faxNumber;
    }
    public String GetUrl(){
        return this.url;
    }
}
