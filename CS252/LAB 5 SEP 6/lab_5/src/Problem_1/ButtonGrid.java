package Problem_1;


import javax.swing.*;
import java.awt.*;
import java.applet.Applet;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ButtonGrid extends Applet implements ActionListener {
    private JFrame frame = new JFrame();
    private JButton[][] button= new JButton[10][10];
    public ButtonGrid(){
        frame.setSize(900,900);
        frame.setTitle("Magic Grid");
        frame.setLayout(new GridLayout(10,10));
        int i,j;
        for(i=0;i<10;i++){
            for(j=0;j<10;j++) {
                button[i][j]=new JButton("");
                button[i][j].addActionListener(this);
                button[i][j].setBackground(Color.YELLOW);
                frame.add(button[i][j]);
            }
        }
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }

    public void actionPerformed(ActionEvent event){
        Object source = event.getSource();
        int i,j,xi=0,xj=0;
        for(i=0;i<10;i++){
            for(j=0;j<10;j++){
                if(source==button[i][j]){
                    xi=i;
                    xj=j;
                    button[i][j].setText(String.format("%d:%d", i,j));
                }
                else{
                    button[i][j].setBackground(Color.YELLOW);
                    button[i][j].setText("");
                }
            }
        }
        button[xi][xj].setBackground(Color.RED);
        int mvi,mvj;
        mvi=xi+1;
        mvj=xj+1;
        while(mvi>=0 && mvi<10 && mvj>=0 && mvj<10){
            button[mvi][mvj].setBackground(Color.RED);
            mvi++;
            mvj++;
        }
        mvi=xi+1;
        mvj=xj-1;
        while(mvi>=0 && mvi<10 && mvj>=0 && mvj<10){
            button[mvi][mvj].setBackground(Color.RED);
            mvi++;
            mvj--;
        }
        mvi=xi-1;
        mvj=xj+1;
        while(mvi>=0 && mvi<10 && mvj>=0 && mvj<10){
            button[mvi][mvj].setBackground(Color.RED);
            mvi--;
            mvj++;
        }
        mvi=xi-1;
        mvj=xj-1;
        while(mvi>=0 && mvi<10 && mvj>=0 && mvj<10){
            button[mvi][mvj].setBackground(Color.RED);
            mvi--;
            mvj--;
        }
    }

}