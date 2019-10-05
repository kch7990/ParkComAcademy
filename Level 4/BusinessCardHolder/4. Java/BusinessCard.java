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
public class BusinessCard {
    private Company company;
    private Personal personal;
    
    public BusinessCard(){
        
    }
    public BusinessCard(String companyName, String address, String companyTelephoneNumber, String faxNumber, String url, 
            String personalName, String personalTelephoneNumber, String emailAddress, String position){
        this.company=new Company(companyName, address, companyTelephoneNumber, faxNumber, url);
        this.personal=new Personal(personalName, personalTelephoneNumber, emailAddress, position);
    }
    public boolean IsEqual(BusinessCard other){
        boolean ret=false;
        if(this.company.IsEqual(other.company)==true &&
                this.personal.IsEqual(other.personal)==true){
            ret=true;
        }
        return ret;
    }
    public boolean IsNotEqual(BusinessCard other){
        boolean ret=false;
        if(this.company.IsNotEqual(other.company)==true ||
                this.personal.IsNotEqual(other.personal)==true){
            ret=true;
        }
        return ret;
    }
    public String GetCompanyName(){
        return this.company.GetName();
    }
    public String GetAddress(){
        return this.company.GetAddress();
    }
    public String GetCompanyTelephoneNumber(){
        return this.company.GetTelephoneNumber();
    }
    public String GetFaxNumber(){
        return this.company.GetFaxNumber();
    }
    public String GetUrl(){
        return this.company.GetUrl();
    }
    public String GetPersonalName(){
        return this.personal.GetName();
    }
    public String GetPersonalTelephoneNumber(){
        return this.personal.GetTelephoneNumber();
    }
    public String GetEmailAddress(){
        return this.personal.GetEmailAddress();
    }
    public String GetPosition(){
        return this.personal.GetPosition();
    }
}
