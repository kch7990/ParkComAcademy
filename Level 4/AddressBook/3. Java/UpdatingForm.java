
package addressbook;
import javax.swing.table.DefaultTableModel;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kch79
 */
public class UpdatingForm extends javax.swing.JFrame {
    AddressBook addressBook;
    /**
     * Creates new form UpdatingForm
     */
    public UpdatingForm() {
        //1. 윈도우가 생성될 때
        initComponents();
        //1.1. 주소록을 만든다.
        this.addressBook=new AddressBook(10000);
        //적재하다.
        Load();
        //적재한 만큼 리스트뷰 컨트롤에 항목을 추가하다.
        Personal personal;
        int i=0;
        while(i<this.addressBook.GetLength()){
            String number;
            number=Integer.toString(i+1);
            personal=this.addressBook.GetAt(i);
            DefaultTableModel model=(DefaultTableModel)IDC_LIST_PERSONALS.getModel();
            model.addRow(new Object[]{number, personal.GetName(), personal.GetAddress(), personal.GetTelephoneNumber(), personal.GetEmailAddress()});
            i++;
        }
    }

    public void Load() {
        Connection conn=null;
        Statement stmt=null;        
        try{
            conn=DriverManager.getConnection("jdbc:mysql://localhost/AddressBook", "root", "preta27531@");
            stmt=conn.createStatement();
            String sql="SELECT Personal.name, Personal.address, Personal.telephoneNumber, Personal.emailAddress FROM Personal;";
            ResultSet rs=stmt.executeQuery(sql);
            String name;
            String address;
            String telephoneNumber;
            String emailAddress;
            while(rs.next()){
                name=rs.getString(1);
                address=rs.getString(2);
                telephoneNumber=rs.getString(3);
                emailAddress=rs.getString(4);
                this.addressBook.Record(name, address, telephoneNumber, emailAddress);
            }
            rs.close();
            stmt.close();
            conn.close();
        }catch(SQLException ex){
            ex.printStackTrace();
        }
        

    }
    public void Save() {        
        Connection conn=null;
        Statement stmt=null;
        try{
            conn=DriverManager.getConnection("jdbc:mysql://localhost/AddressBook", "root", "preta27531@");
            stmt=conn.createStatement(); //Connection
            String sql="SELECT Personal.code FROM Personal";
            ResultSet rs=stmt.executeQuery(sql); //SELECT Request/Response
            stmt=conn.createStatement();
            sql="DELETE FROM Personal;";
            stmt.executeUpdate(sql); //DELETE Request
            String code;
            int i=0;
            Personal personal;
            while(rs.next()){
                personal=this.addressBook.GetAt(i);
                code=rs.getString(1);
                sql=String.format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) "+
                 "VALUES('%s', '%s', '%s', '%s', '%s');",
                 code, personal.GetName(), personal.GetAddress(), personal.GetTelephoneNumber(), personal.GetEmailAddress());
                stmt.executeUpdate(sql); //INSERT Request
                i++;
            }
            rs.close();
            stmt.close();
            conn.close();
        }catch(SQLException ex){
            ex.printStackTrace();
        }
    }
    public void Insert(int index){
        String code=MakeCode();
        Personal personal=this.addressBook.GetAt(index);
        Connection conn=null;
        Statement stmt=null;
        String sql="";
        try{            
            conn=DriverManager.getConnection("jdbc:mysql://localhost/AddressBook", "root", "preta27531@");
            stmt=conn.createStatement(); //Connection
            sql=String.format("INSERT INTO Personal(code, name, address, telephoneNumber, emailAddress) "+
                "VALUES('%s', '%s', '%s', '%s', '%s');",
                code, personal.GetName(), personal.GetAddress(), personal.GetTelephoneNumber(), personal.GetEmailAddress());       
            stmt.executeUpdate(sql); //INSERT Request
            stmt.close();
            conn.close();
        }catch(SQLException ex){
            ex.printStackTrace();
        }
    }
    public void Delete(int index){
        Connection conn=null;
        Statement stmt=null;
        ResultSet rs = null;
        String sql="SELECT Personal.code FROM Personal;";
        try{
            conn=DriverManager.getConnection("jdbc:mysql://localhost/AddressBook", "root", "preta27531@");
            stmt=conn.createStatement(); //Connection
            rs=stmt.executeQuery(sql); //SELET Request/Response
            int i=0;
            rs.relative(index+1);
            String code=rs.getString(1);
            sql=String.format("DELETE FROM Personal WHERE code='%s';", code);
            stmt.executeUpdate(sql); //DELETE Request
            rs.close();
            stmt.close();
            conn.close(); //Disconnection
        }catch(SQLException ex){
            ex.printStackTrace();
        }
    }
    public void Modify(int index){
        Personal personal=this.addressBook.GetAt(index);
        Connection conn=null;
        Statement stmt=null;
        ResultSet rs=null;
        String sql="SELECT Personal.code FROM Personal;";
        try{
            conn=DriverManager.getConnection("jdbc:mysql://localhost/AddressBook", "root", "preta27531@");
            stmt=conn.createStatement(); //Connection
            rs=stmt.executeQuery(sql); //SELECT Request/Response
            rs.relative(index+1);
            String code=rs.getString(1);
            sql=String.format("UPDATE Personal SET address='%s', telephoneNumber='%s', emailAddress='%s' WHERE personal.code='%s';",
                    personal.GetAddress(), personal.GetTelephoneNumber(), personal.GetEmailAddress(), code);
            stmt.executeUpdate(sql); //UPDATE Request
            rs.close();
            stmt.close();
            conn.close(); //Disconnection
        }catch(SQLException ex){
            ex.printStackTrace();
        }
    }
    public String MakeCode(){
        Connection conn=null;
        Statement stmt=null;
        ResultSet rs=null;
        String sql="SELECT Personal.code FROM Personal ORDER BY code DESC;";
        String code="P0001";
        int codeNumber;
        try{
            conn=DriverManager.getConnection("jdbc:mysql://localhost/AddressBook", "root", "preta27531@");
            stmt=conn.createStatement(); //Connection
            rs=stmt.executeQuery(sql); //SELECT Request/Response
            if(rs.next()){
                code=rs.getString(1);
                String numberCode=code.replaceFirst("P", "");
                codeNumber=Integer.parseInt(numberCode);
                code=numberCode.format("P%04d", codeNumber+1);
            }
            rs.close();
            stmt.close();
            conn.close(); //Disconnection
        }catch(SQLException ex){
            ex.printStackTrace();
        }
        return code;
    }
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jDialog1 = new javax.swing.JDialog();
        jDialog2 = new javax.swing.JDialog();
        jDialog3 = new javax.swing.JDialog();
        jDialog4 = new javax.swing.JDialog();
        jFrame1 = new javax.swing.JFrame();
        jFileChooser1 = new javax.swing.JFileChooser();
        IDC_STATIC_PERSONAL = new javax.swing.JPanel();
        IDC_EDIT_NAME = new javax.swing.JTextField();
        IDC_STATIC_NAME = new javax.swing.JLabel();
        IDC_STATIC_ADDRESS = new javax.swing.JLabel();
        IDC_STATIC_TELEPHONENUMBER = new javax.swing.JLabel();
        IDC_STATIC_EMAILADDRESS = new javax.swing.JLabel();
        IDC_EDIT_ADDRESS = new javax.swing.JTextField();
        IDC_EDIT_TELEPHONENUMBER = new javax.swing.JTextField();
        IDC_EDIT_EMAILADDRESS = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        IDC_LIST_PERSONALS = new javax.swing.JTable();
        IDC_BUTTON_RECORD = new javax.swing.JButton();
        IDC_BUTTON_FIND = new javax.swing.JButton();
        IDC_BUTTON_CORRECT = new javax.swing.JButton();
        IDC_BUTTON_ERASE = new javax.swing.JButton();
        IDC_BUTTON_ARRANGE = new javax.swing.JButton();

        javax.swing.GroupLayout jDialog1Layout = new javax.swing.GroupLayout(jDialog1.getContentPane());
        jDialog1.getContentPane().setLayout(jDialog1Layout);
        jDialog1Layout.setHorizontalGroup(
            jDialog1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jDialog1Layout.setVerticalGroup(
            jDialog1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jDialog2Layout = new javax.swing.GroupLayout(jDialog2.getContentPane());
        jDialog2.getContentPane().setLayout(jDialog2Layout);
        jDialog2Layout.setHorizontalGroup(
            jDialog2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jDialog2Layout.setVerticalGroup(
            jDialog2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jDialog3Layout = new javax.swing.GroupLayout(jDialog3.getContentPane());
        jDialog3.getContentPane().setLayout(jDialog3Layout);
        jDialog3Layout.setHorizontalGroup(
            jDialog3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jDialog3Layout.setVerticalGroup(
            jDialog3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jDialog4Layout = new javax.swing.GroupLayout(jDialog4.getContentPane());
        jDialog4.getContentPane().setLayout(jDialog4Layout);
        jDialog4Layout.setHorizontalGroup(
            jDialog4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jDialog4Layout.setVerticalGroup(
            jDialog4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout jFrame1Layout = new javax.swing.GroupLayout(jFrame1.getContentPane());
        jFrame1.getContentPane().setLayout(jFrame1Layout);
        jFrame1Layout.setHorizontalGroup(
            jFrame1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 400, Short.MAX_VALUE)
        );
        jFrame1Layout.setVerticalGroup(
            jFrame1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 300, Short.MAX_VALUE)
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("주소록");
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });

        IDC_STATIC_PERSONAL.setToolTipText("개인");

        IDC_EDIT_NAME.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_EDIT_NAMEActionPerformed(evt);
            }
        });

        IDC_STATIC_NAME.setText("성         명");

        IDC_STATIC_ADDRESS.setText("주         소");

        IDC_STATIC_TELEPHONENUMBER.setText("전화   번호");

        IDC_STATIC_EMAILADDRESS.setText("이메일주소");

        IDC_EDIT_ADDRESS.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_EDIT_ADDRESSActionPerformed(evt);
            }
        });

        IDC_EDIT_TELEPHONENUMBER.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_EDIT_TELEPHONENUMBERActionPerformed(evt);
            }
        });

        jLabel5.setText("개인");

        javax.swing.GroupLayout IDC_STATIC_PERSONALLayout = new javax.swing.GroupLayout(IDC_STATIC_PERSONAL);
        IDC_STATIC_PERSONAL.setLayout(IDC_STATIC_PERSONALLayout);
        IDC_STATIC_PERSONALLayout.setHorizontalGroup(
            IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(IDC_STATIC_PERSONALLayout.createSequentialGroup()
                .addGap(43, 43, 43)
                .addGroup(IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(IDC_STATIC_PERSONALLayout.createSequentialGroup()
                        .addComponent(IDC_STATIC_EMAILADDRESS)
                        .addGap(66, 66, 66)
                        .addComponent(IDC_EDIT_EMAILADDRESS))
                    .addGroup(IDC_STATIC_PERSONALLayout.createSequentialGroup()
                        .addComponent(IDC_STATIC_NAME)
                        .addGap(66, 66, 66)
                        .addComponent(IDC_EDIT_NAME))
                    .addGroup(IDC_STATIC_PERSONALLayout.createSequentialGroup()
                        .addComponent(IDC_STATIC_ADDRESS)
                        .addGap(66, 66, 66)
                        .addComponent(IDC_EDIT_ADDRESS))
                    .addGroup(IDC_STATIC_PERSONALLayout.createSequentialGroup()
                        .addComponent(IDC_STATIC_TELEPHONENUMBER)
                        .addGap(66, 66, 66)
                        .addComponent(IDC_EDIT_TELEPHONENUMBER)))
                .addContainerGap())
            .addComponent(jLabel5)
        );
        IDC_STATIC_PERSONALLayout.setVerticalGroup(
            IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(IDC_STATIC_PERSONALLayout.createSequentialGroup()
                .addComponent(jLabel5)
                .addGap(16, 16, 16)
                .addGroup(IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(IDC_STATIC_NAME)
                    .addComponent(IDC_EDIT_NAME, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(IDC_STATIC_ADDRESS)
                    .addComponent(IDC_EDIT_ADDRESS, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(IDC_STATIC_TELEPHONENUMBER)
                    .addComponent(IDC_EDIT_TELEPHONENUMBER, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(IDC_STATIC_PERSONALLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(IDC_STATIC_EMAILADDRESS)
                    .addComponent(IDC_EDIT_EMAILADDRESS, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(42, Short.MAX_VALUE))
        );

        IDC_LIST_PERSONALS.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "번호", "성명", "주소", "전화번호", "이메일주소"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class, java.lang.String.class
            };
            boolean[] canEdit = new boolean [] {
                false, false, false, false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        IDC_LIST_PERSONALS.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                IDC_LIST_PERSONALSMouseClicked(evt);
            }
        });
        jScrollPane2.setViewportView(IDC_LIST_PERSONALS);

        IDC_BUTTON_RECORD.setText("기재하기");
        IDC_BUTTON_RECORD.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_BUTTON_RECORDActionPerformed(evt);
            }
        });

        IDC_BUTTON_FIND.setText("찾      기");
        IDC_BUTTON_FIND.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_BUTTON_FINDActionPerformed(evt);
            }
        });

        IDC_BUTTON_CORRECT.setText("고  치 기");
        IDC_BUTTON_CORRECT.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_BUTTON_CORRECTActionPerformed(evt);
            }
        });

        IDC_BUTTON_ERASE.setText("지  우 기");
        IDC_BUTTON_ERASE.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_BUTTON_ERASEActionPerformed(evt);
            }
        });

        IDC_BUTTON_ARRANGE.setText("정리하기");
        IDC_BUTTON_ARRANGE.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                IDC_BUTTON_ARRANGEActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                    .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 603, Short.MAX_VALUE)
                    .addComponent(IDC_STATIC_PERSONAL, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 40, Short.MAX_VALUE)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(IDC_BUTTON_FIND, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(IDC_BUTTON_RECORD, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(IDC_BUTTON_CORRECT, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(IDC_BUTTON_ERASE, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(IDC_BUTTON_ARRANGE, javax.swing.GroupLayout.Alignment.TRAILING))
                .addGap(46, 46, 46))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(IDC_STATIC_PERSONAL, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(50, 50, 50)
                        .addComponent(IDC_BUTTON_RECORD)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(IDC_BUTTON_FIND)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(IDC_BUTTON_CORRECT)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(IDC_BUTTON_ERASE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(IDC_BUTTON_ARRANGE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 181, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(32, Short.MAX_VALUE))
        );

        IDC_STATIC_PERSONAL.getAccessibleContext().setAccessibleName("개인");

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void IDC_EDIT_NAMEActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_EDIT_NAMEActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_IDC_EDIT_NAMEActionPerformed

    private void IDC_EDIT_ADDRESSActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_EDIT_ADDRESSActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_IDC_EDIT_ADDRESSActionPerformed

    private void IDC_EDIT_TELEPHONENUMBERActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_EDIT_TELEPHONENUMBERActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_IDC_EDIT_TELEPHONENUMBERActionPerformed

    private void IDC_BUTTON_RECORDActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_BUTTON_RECORDActionPerformed
        // TODO add your handling code here:
        //2. 기재하기 버튼을 클릭했을 때
        //2.1. 개인을 읽는다.
        String name=IDC_EDIT_NAME.getText();
        String address=IDC_EDIT_ADDRESS.getText();
        String telephoneNumber=IDC_EDIT_TELEPHONENUMBER.getText();
        String emailAddress=IDC_EDIT_EMAILADDRESS.getText();
        //2.2. 주소록에서 기재한다.
        int index=this.addressBook.Record(name, address, telephoneNumber, emailAddress);
        Personal personal=this.addressBook.GetAt(index);
        //데이터베이스에 삽입한다.
        Insert(index);
        //2.3. 리스트뷰 컨트롤에 항목을 추가한다.
        String number;
        number=Integer.toString(index+1);
        DefaultTableModel model=(DefaultTableModel)IDC_LIST_PERSONALS.getModel();
        model.addRow(new Object[]{number, personal.GetName(), personal.GetAddress(), personal.GetTelephoneNumber(), personal.GetEmailAddress()});
    }//GEN-LAST:event_IDC_BUTTON_RECORDActionPerformed

    private void IDC_BUTTON_FINDActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_BUTTON_FINDActionPerformed
        // TODO add your handling code here:
        //3. 찾기 버튼을 클릭했을 때
        //3.1. 찾기 윈도우를 출력한다.
        new FindingForm(this).setVisible(true);
    }//GEN-LAST:event_IDC_BUTTON_FINDActionPerformed

    private void IDC_BUTTON_CORRECTActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_BUTTON_CORRECTActionPerformed
        // TODO add your handling code here:
        //4. 고치기 버튼을 클릭했을 때
        //4.1. 개인을 읽는다.
        String address=IDC_EDIT_ADDRESS.getText();
        String telephoneNumber=IDC_EDIT_TELEPHONENUMBER.getText();
        String emailAddress=IDC_EDIT_EMAILADDRESS.getText();
        //4.2. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
        int index=IDC_LIST_PERSONALS.getSelectedRow();
        //4.3. 주소록에서 고치다.
        index=this.addressBook.Correct(index, address, telephoneNumber, emailAddress);
        
        Modify(index);
        
        Personal personal=this.addressBook.GetAt(index);
        //4.4. 리스트뷰 컨트롤의 항목을 수정한다.
        IDC_LIST_PERSONALS.setValueAt(personal.GetAddress(), index, 2);
        IDC_LIST_PERSONALS.setValueAt(personal.GetTelephoneNumber(), index, 3);
        IDC_LIST_PERSONALS.setValueAt(personal.GetEmailAddress(), index, 4);
    }//GEN-LAST:event_IDC_BUTTON_CORRECTActionPerformed

    private void IDC_BUTTON_ERASEActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_BUTTON_ERASEActionPerformed
        // TODO add your handling code here:
        //5. 지우기 버튼을 클릭했을 때
        //5.1. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
        int index=IDC_LIST_PERSONALS.getSelectedRow();
        //5.2. 주소록에서 지우다.
        this.addressBook.Erase(index);
        
        Delete(index);
        //5.3. 리스트뷰 컨트롤의 항목을 지운다.
        DefaultTableModel mode=(DefaultTableModel)IDC_LIST_PERSONALS.getModel();
        mode.removeRow(index);
        //5.4. 선택된 위치부터 마지막까지 번호를 고친다.
        String number;
        while(index<this.addressBook.GetLength()){
            number=Integer.toString(index+1);
            IDC_LIST_PERSONALS.setValueAt(number, index, 0);
            index++;
        }
    }//GEN-LAST:event_IDC_BUTTON_ERASEActionPerformed

    private void IDC_BUTTON_ARRANGEActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_IDC_BUTTON_ARRANGEActionPerformed
        // TODO add your handling code here:
        //6. 정리하기 버튼을 클릭했을 때
        //6.1. 주소록에서 정리하다.
        this.addressBook.Arrange();
        Save();
        //6.2. 리스트뷰 컨트롤의 모든 항목을 지운다.
        DefaultTableModel model=(DefaultTableModel)IDC_LIST_PERSONALS.getModel();
        model.setNumRows(0);
        //6.3. 리스트뷰 컨트롤의 주소록에 적힌 개수만큼 항목에 추가한다.
        String number;
        Personal personal;
        int i=0;
        while(i<this.addressBook.GetLength()){
            number=Integer.toString(i+1);
            personal=this.addressBook.GetAt(i);
            model.addRow(new Object[]{number, personal.GetName(), personal.GetAddress(), personal.GetTelephoneNumber(), personal.GetEmailAddress()});
            i++;
        }
    }//GEN-LAST:event_IDC_BUTTON_ARRANGEActionPerformed

    private void IDC_LIST_PERSONALSMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_IDC_LIST_PERSONALSMouseClicked
        // TODO add your handling code here:
        //7. 리스트뷰 컨트롤의 항목을 클릭했을 때
        //7.1. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
        int index=IDC_LIST_PERSONALS.getSelectedRow();
        //7.2. 선택된 위치의 항목을 읽는다.
        String name=(String)IDC_LIST_PERSONALS.getValueAt(index, 1);
        String address=(String)IDC_LIST_PERSONALS.getValueAt(index, 2);
        String telephoneNumber=(String)IDC_LIST_PERSONALS.getValueAt(index, 3);
        String emailAddress=(String)IDC_LIST_PERSONALS.getValueAt(index, 4);
        //7.3. 개인에 출력하다.
        IDC_EDIT_NAME.setText(name);
        IDC_EDIT_ADDRESS.setText(address);
        IDC_EDIT_TELEPHONENUMBER.setText(telephoneNumber);
        IDC_EDIT_EMAILADDRESS.setText(emailAddress);
    }//GEN-LAST:event_IDC_LIST_PERSONALSMouseClicked

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        // TODO add your handling code here:
        Save();
    }//GEN-LAST:event_formWindowClosing
    
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(UpdatingForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(UpdatingForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(UpdatingForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(UpdatingForm.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new UpdatingForm().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton IDC_BUTTON_ARRANGE;
    private javax.swing.JButton IDC_BUTTON_CORRECT;
    private javax.swing.JButton IDC_BUTTON_ERASE;
    private javax.swing.JButton IDC_BUTTON_FIND;
    private javax.swing.JButton IDC_BUTTON_RECORD;
    javax.swing.JTextField IDC_EDIT_ADDRESS;
    javax.swing.JTextField IDC_EDIT_EMAILADDRESS;
    javax.swing.JTextField IDC_EDIT_NAME;
    javax.swing.JTextField IDC_EDIT_TELEPHONENUMBER;
    javax.swing.JTable IDC_LIST_PERSONALS;
    private javax.swing.JLabel IDC_STATIC_ADDRESS;
    private javax.swing.JLabel IDC_STATIC_EMAILADDRESS;
    private javax.swing.JLabel IDC_STATIC_NAME;
    private javax.swing.JPanel IDC_STATIC_PERSONAL;
    private javax.swing.JLabel IDC_STATIC_TELEPHONENUMBER;
    private javax.swing.JDialog jDialog1;
    private javax.swing.JDialog jDialog2;
    private javax.swing.JDialog jDialog3;
    private javax.swing.JDialog jDialog4;
    private javax.swing.JFileChooser jFileChooser1;
    private javax.swing.JFrame jFrame1;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JScrollPane jScrollPane2;
    // End of variables declaration//GEN-END:variables
}
