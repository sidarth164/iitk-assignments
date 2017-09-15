package sample;

import com.sun.glass.ui.CommonDialogs;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TextArea;
import javafx.stage.FileChooser;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

public class EditorController {
    @FXML
    private TextArea text;
    private TextFile currentTextFile;
    private EditorModel model;
    public List<String> originalData;

    public  EditorController(EditorModel model){
        this.model=model;
    }

    @FXML
    private void onNew(){

    }

    @FXML
    private void onOpen(){
        FileChooser fileChooser = new FileChooser();
        //fileChooser.setInitialDirectory(new File("~/"));
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("JAVA FILES","*.java"));
        File file=fileChooser.showOpenDialog(null);
        if(file!=null){
            IOResult<TextFile> io = model.load(file.toPath());

            if(io.ok && io.hasData()){
                currentTextFile = io.data;
                originalData = io.data.content;
                text.clear();
                currentTextFile.getContent().forEach(text::appendText);
            } else {
                System.out.println("Failed!");
            }
        }
    }
    @FXML
    private void onCompile(){
            onSave();
            // Command to create an external process
            String command = currentTextFile.file.toString();
        try{
            // Running the above command
            Runtime run  = Runtime.getRuntime();
            Process proc = run.exec("javac "+command);
            proc.wait();
            if(proc.exitValue()!=0){
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setHeaderText(null);
                alert.setContentText("Check your code again");
                alert.showAndWait();
            }else {
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setHeaderText(null);
                alert.setContentText("Hurrah!");
                alert.showAndWait();
            }
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void onSave(){
        TextFile textFile = new TextFile(currentTextFile.getFile(), Arrays.asList(text.getText().split("\n")));
        model.save(textFile);
    }

    @FXML
    private void onSaveAs(){
        FileChooser fileChooser = new FileChooser();
        //fileChooser.setInitialDirectory(new File("~/"));
        fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("JAVA FILES","*.java"));
        File file=fileChooser.showSaveDialog(null);
        if(file!=null){
            currentTextFile.file=file.toPath();
            TextFile textFile = new TextFile(currentTextFile.getFile(), Arrays.asList(text.getText().split("\n")));
            model.save(textFile);
        } else {
            System.out.println("Failed!!");
        }

    }

    @FXML
    private void onAbout(){
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setHeaderText(null);
        alert.setContentText("Name- Siddharth Agrawal\nRoll Number 150716");
        alert.show();
    }

    @FXML
    private void onClose(){
        //if(!originalData.equals(currentTextFile.content)){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText(null);
            alert.setContentText("Please Save Content");
            alert.showAndWait();
        //}
        onSave();
        model.close();
    }

    @FXML
    private void onQuit(){
        if(originalData!=currentTextFile.content){
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setHeaderText(null);
            alert.setContentText("Please Save Content");
            alert.show();
        }
        onSave();
        model.close();
    }

}
