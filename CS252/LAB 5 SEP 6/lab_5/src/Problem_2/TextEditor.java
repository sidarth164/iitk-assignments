package Problem_2;

import javax.swing.*;
import java.applet.Applet;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.*;

public class TextEditor extends Applet implements ActionListener{
    JFrame frame = new JFrame();
    JMenuBar menuBar;
    JMenu edit,file;
    JMenuItem menuItem;
    JTextArea text = new JTextArea();

    public TextEditor(){
        frame.setSize(1024,1024);
        frame.setTitle("Text Editor");

        //Create the menu bar.
        menuBar = new JMenuBar();

//Build the first menu.

        file = new JMenu("File");
        file.getAccessibleContext().setAccessibleDescription(
                "File");
        menuBar.add(file);

        edit = new JMenu("Edit");
        edit.getAccessibleContext().setAccessibleDescription(
                "Edit");
        menuBar.add(edit);

//a group of JMenuItems

        menuItem = new JMenuItem("Open");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("Open");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_O, ActionEvent.ALT_MASK));
        file.add(menuItem);

        menuItem = new JMenuItem("Save");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("Save");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_S, ActionEvent.ALT_MASK));
        file.add(menuItem);

        menuItem = new JMenuItem("Save As");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("SaveAs");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_S, ActionEvent.ALT_MASK | ActionEvent.CTRL_MASK));
        file.add(menuItem);

        menuItem = new JMenuItem("Exit");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("Exit");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_W, ActionEvent.ALT_MASK));
        file.add(menuItem);

        menuItem = new JMenuItem("Cut");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("Cut");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_X, ActionEvent.ALT_MASK));
        edit.add(menuItem);

        menuItem = new JMenuItem("Copy");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("Copy");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_C, ActionEvent.ALT_MASK));
        edit.add(menuItem);

        menuItem = new JMenuItem("Paste");
        menuItem.addActionListener(this);
        menuItem.setActionCommand("Paste");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_V, ActionEvent.ALT_MASK));
        edit.add(menuItem);

        menuItem = new JMenuItem("Select All");
        menuItem.setAccelerator(KeyStroke.getKeyStroke(
                KeyEvent.VK_A, ActionEvent.ALT_MASK));
        menuItem.addActionListener(this);
        menuItem.setActionCommand("SelectAll");
        edit.add(menuItem);

//...
        frame.setJMenuBar(menuBar);

        frame.add(text);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    JFileChooser chooser = new JFileChooser();
    String copytext="";
    @Override
    public void actionPerformed(ActionEvent event) {
        String label = event.getActionCommand();
        if(label.equals("Open")){
            int i=chooser.showOpenDialog(this);
            if(i==JFileChooser.APPROVE_OPTION){
                File f=chooser.getSelectedFile();
                String filepath=f.getPath();
                try{
                    BufferedReader br=new BufferedReader(new FileReader(filepath));
                    String s1="",s2="";
                    while((s1=br.readLine())!=null){
                        s2+=s1+"\n";
                    }
                    text.setText(s2);
                    br.close();
                }catch (Exception ex) {ex.printStackTrace();  }
            }
        }
        if(label.equals("Save")){
            File f=chooser.getSelectedFile();
            String filepath=f.getPath();
            try{
                BufferedWriter br=new BufferedWriter(new FileWriter(filepath));
                String s=text.getText();
                br.write(s);
                br.close();
            }catch (Exception ex) {ex.printStackTrace();  }
        }
        if(label.equals("SaveAs")){

        }
        if(label.equals("Exit")){
            System.exit(0);
        }
        if(label.equals("Copy")){
            copytext = text.getSelectedText();
        }
        if(label.equals("Cut")){
            copytext = text.getSelectedText();
            text.setText(text.getText().replace(copytext,""));
        }
        if(label.equals("Paste")){
            text.append(copytext);
        }
        if(label.equals("SelectAll")){
            text.selectAll();
        }
    }
}
