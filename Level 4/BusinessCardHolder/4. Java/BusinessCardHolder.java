/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businesscardholder;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.ListIterator;

/**
 *
 * @author Taehoo
 */
public class BusinessCardHolder {
    public BusinessCardHolder(){
        this.businessCards = new LinkedList<BusinessCard>();
        this.length = 0;
        this.current = null;
    }
    
    public BusinessCard PutIn(BusinessCard businessCard){
       this.businessCards.addLast(businessCard);
       this.length++;
       BusinessCard index = this.businessCards.getLast();
       this.current = index;
       
       return this.current;
    }
    
    public BusinessCard[] Find(String name){
        BusinessCard[] indexes = new BusinessCard[this.length];
        ListIterator<BusinessCard> listIterator = this.businessCards.listIterator();
        BusinessCard current;
        int count=0;
        
        
        while(listIterator.hasNext()){
            current = listIterator.next();
            if(current.GetPersonalName().compareTo(name) == 0){
                indexes[count] = current;
                count++;
            }
        }
        // �뿰寃곕━�뒪�듃�뿉 泥섏쓬遺��꽣 �걹源뚯� 諛섎났�븯硫댁꽌
        // 留ㅺ컻蹂��닔濡쒕컺�� �씠由꾧낵 紐낇븿�뿉 �궗�엺�씠由꾪븯怨� 媛숈쑝硫�
        // �씤�뜳�떆利덉뿉 ���옣�븿
        indexes = Arrays.copyOf(indexes, count);
        
        return indexes;
 
    }
    public BusinessCard FindByCompanyName(String companyName){
        // �뿰寃곕━�뒪�듃�뿉�꽌 泥섏쓬遺��꽣 �걹源뚯� 洹몃━怨� 紐낇븿�쓽 �긽�샇媛� 留ㅺ컻蹂��닔 �긽�샇�옉 �떎瑜쇰룞�븞 諛섎났�븿
        int index =0;
        BusinessCard businessCard = null;
        
        this.current = this.businessCards.peekFirst();
        
        while(index<this.businessCards.size() && this.current.GetCompanyName().compareTo(companyName) !=0){
            this.current = this.businessCards.get(index);
            index++;
        }
        if(index<this.businessCards.size()){
            businessCard = this.current;
        }
        return businessCard;
    }
    public BusinessCard PutOut(BusinessCard index){
        int i = this.businessCards.indexOf(index);
        BusinessCard businessCard=null;
        businessCard = this.businessCards.get(i);
        this.businessCards.remove(i);
        this.length--;
        
        if(this.businessCards.size() != 0){
            this.current = this.businessCards.get(i);
        }
        else{
            this.current=null;
        }
        return businessCard;
    }
    public BusinessCard First(){
        this.current = this.businessCards.peekFirst();
        
        return this.current;
    }
    public BusinessCard Previous(){
        int index = this.businessCards.indexOf(this.current);
        index--;
        if(index < 0 ){
            index = 0;
        }
        if(this.length>0){
            this.current = this.businessCards.get(index);
        }
        return this.current;
    }
    public BusinessCard Next(){
        int index = this.businessCards.indexOf(this.current);
        index++;
        if(index >= this.businessCards.size() ){
            index = this.businessCards.size() - 1;
        }
        if(this.length>0){
            this.current = this.businessCards.get(index);
        }
        return this.current;
    }
    public BusinessCard Last(){
        this.current = this.businessCards.peekLast();
        
        return this.current;
    }
    public BusinessCard Move(BusinessCard index){
        int i = this.businessCards.indexOf(index);
        this.current = this.businessCards.get(i);
        return this.current;
    }
    public int GetLength(){
        return this.length;
    }
    public BusinessCard GetCurrent(){
        return this.current;
    }
    
    private LinkedList<BusinessCard> businessCards;
    private int length;
    private BusinessCard current;
    /*
    public static void main(String[] args) {
        BusinessCard businessCard1 = new BusinessCard("�솉而�", "�꽌�슱�떆 留덊룷援�", "02111", "021112", "hong.com","�솉湲몃룞", " 01011111", "hong@", "�궗�옣");
	BusinessCard businessCard2 = new BusinessCard("怨좎뺨", "���쟾�떆 �쑀�꽦援�", "041111", "041112", "ko.com","怨좉만�룞", "0102222", "ko@", "怨쇱옣");
	BusinessCard businessCard3 = new BusinessCard("�씠而�", "��援ъ떆 �떖�꽌援�", "05223333", "0522333", "Lee.com","�솉湲몃룞", "01022222", "hong2@", "�궗�썝");
	BusinessCard businessCard4 = new BusinessCard("�솉而�", "�꽌�슱�떆 留덊룷援�", "021112", "0211123", "hong.com",	"�젙湲몃룞", "010333333", "jung@", "��由�");
        BusinessCardHolder businessCardHolder = new BusinessCardHolder();
        BusinessCard index;
        index = businessCardHolder.PutIn(businessCard1);
        System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
        
        index = businessCardHolder.PutIn(businessCard2);
        System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
        
        index = businessCardHolder.PutIn(businessCard3);
        System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
        
        index = businessCardHolder.PutIn(businessCard4);
        System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
      
        index=businessCardHolder.First();
         System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         
         index=businessCardHolder.Next();
         System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         
         BusinessCard businessCard =businessCardHolder.PutOut(index);
         System.out.println(businessCard.GetCompanyName()+" "+businessCard.GetAddress()+" "+businessCard.GetCompanyTelephoneNumber()+
                " "+businessCard.GetFaxNumber()+" "+businessCard.GetUrl()+" "+ businessCard.GetPersonalName() + " " + businessCard.GetPersonalTelephoneNumber() +
                " " + businessCard.GetEmailAddress() + " " + businessCard.GetPosition() );
         index = businessCardHolder.PutIn(businessCard);
         System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         
         BusinessCard[] indexes;
         indexes = businessCardHolder.Find("�솉湲몃룞");
         int i =0;
         while(i<indexes.length){
             System.out.println(indexes[i].GetCompanyName()+" "+indexes[i].GetAddress()+" "+indexes[i].GetCompanyTelephoneNumber()+
                " "+indexes[i].GetFaxNumber()+" "+indexes[i].GetUrl()+" "+ indexes[i].GetPersonalName() + " " + indexes[i].GetPersonalTelephoneNumber() +
                " " + indexes[i].GetEmailAddress() + " " + indexes[i].GetPosition() );
             i++;
         }
         
         index=businessCardHolder.Last();
         System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         index=businessCardHolder.Previous();
         System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         index=businessCardHolder.FindByCompanyName("�솉而�");
         System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         
         index=businessCardHolder.Move(indexes[0]);
          System.out.println(index.GetCompanyName()+" "+index.GetAddress()+" "+index.GetCompanyTelephoneNumber()+
                " "+index.GetFaxNumber()+" "+index.GetUrl()+" "+ index.GetPersonalName() + " " + index.GetPersonalTelephoneNumber() +
                " " + index.GetEmailAddress() + " " + index.GetPosition() );
         
    }
    */
    
    
    
}
