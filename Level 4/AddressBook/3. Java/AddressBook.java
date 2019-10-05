/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package addressbook;

import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author kch79
 */
public class AddressBook {
    private final ArrayList<Personal> personals;
    private int capacity;
    private int length;

    public AddressBook(int capacity){
        this.personals=new ArrayList<>(capacity);
        this.capacity=capacity;
        this.length=0;
    }
    public int Record(String name, String address, String telephoneNumber, String emailAddress){
        Personal personal=new Personal(name, address, telephoneNumber, emailAddress);
        int index=this.length;
        if(this.length<this.capacity){
            this.personals.add(index, personal);
        }
        else{
            this.personals.add(personal);
            this.capacity++;
        }
        this.length++;
        
        return index;
    }
    public int[] Find(String name){
        int i=0;
        int j=0;
        int count=0;
        
        while(i<this.length){
            if(this.personals.get(i).GetName().compareTo(name)==0){
                count++;
            }
            i++;
        }
        int indexes[]=new int[count];
        i=0;
        while(i<this.length){
            if(this.personals.get(i).GetName().compareTo(name)==0){
                indexes[j]=i;
                j++;
            }
            i++;
        }
        return indexes;
    }
    public int Correct(int index, String address, String telephoneNumber, String emailAddress){
        Personal personal=new Personal(this.personals.get(index).GetName(), address, telephoneNumber, emailAddress);
        this.personals.set(index, personal);
        
        return index;
    }
    public int Erase(int index){
        this.personals.remove(index);
        this.capacity--;
        this.length--;
        
        return -1;
    }
    public void Arrange(){
        int i=0;
        int j;
        Personal min = new Personal();
        int minIndex;
        
        while(i<this.length-1){
            minIndex=i;
            min=this.personals.get(minIndex);
            j=i+1;
            while(j<this.length){
                if(min.GetName().compareTo(this.personals.get(j).GetName())>0){
                    minIndex=j;
                    min=this.personals.get(minIndex);
                }
                j++;
            }
            this.personals.set(minIndex, this.personals.get(i));
            this.personals.set(i, min);
            i++;
        }
    }
    public Personal GetAt(int index){
        return this.personals.get(index);
    }
    public int GetCapacity(){
        return this.capacity;
    }
    public int GetLength(){
        return this.length;
    }
    /*
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        //1. 주소록을 생성하다.
        AddressBook addressBook=new AddressBook(2);
        //2. 홍길동, 서울시, 0101111, hong@을 기재하다.
        int index=addressBook.Record("홍길동", "서울시", "0101111", "hong@");
        Personal personal=new Personal();
        personal=addressBook.GetAt(index);
        System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
        //3. 고길동, 대전시, 0102222, ko@을 기재하다.
        index=addressBook.Record("고길동", "대전시", "0102222", "ko@");
        personal=addressBook.GetAt(index);
        System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
        //4. 정길동, 대구시, 0103333, jung@을 기재하다.
        index=addressBook.Record("정길동", "대구시", "0103333", "jung@");
        personal=addressBook.GetAt(index);
        System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
        //5. 홍길동, 부산시, 0104444, gil@을 기재하다.
        index=addressBook.Record("홍길동", "부산시", "0104444", "gil@");
        personal=addressBook.GetAt(index);
        System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
        //6. 홍길동을 찾다.
        System.out.printf("--------------------------%n");
        int indexes[]=addressBook.Find("홍길동");
        int i=0;
        while(i<indexes.length){
            personal=addressBook.GetAt(indexes[i]);
            System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
            i++;
        }
        //7. 세번째를 제주시로 바꾸다.
        System.out.printf("--------------------------%n");
        index=addressBook.Correct(2, "서울시", "0103333", "jung@");
        personal=addressBook.GetAt(index);        
        System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
        //8. 두번째를 지우다.
        System.out.printf("--------------------------%n");
        index=addressBook.Erase(1);
        if(index==-1){
            System.out.printf("지워졌습니다%n");
        }
        //9. 정리하다.
        System.out.printf("--------------------------%n");
        addressBook.Arrange();
        i=0;
        while(i<addressBook.GetLength()){
            personal=addressBook.GetAt(i);
            System.out.println(personal.GetName() +" "+ personal.GetAddress() +" "+ personal.GetTelephoneNumber() +" "+ personal.GetEmailAddress());
            i++;
        }
    }
    */
}